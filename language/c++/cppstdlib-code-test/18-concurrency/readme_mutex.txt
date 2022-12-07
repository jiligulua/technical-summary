18.4线程同步化与concurrency（并发）问题

为什么并发访问会造成问题？
1.C++标准要求程序有一致的可观测行为，但给予编译器厂商或硬件厂商相当的自由度和能力产生代码，以受益于“最快的速度”，而“安全性”不再默认考虑范围之内。
比如：不保证产生相同的汇编码，不明确函数调用的读取次序，
2.编译器和厂商会重新安排语句，如去除无用代码，预先读取数据等

什么情况下可能出错？
1.未同步化的数据访问
  除非另有说明，C++标准库提供的函数通常不支持“读或写”动作和另一个“写”动作（写到同一笔数据）并发执行
2.写至半途的数据
  对基本数据类型，标准不保证读写是atomic（不可分割的，是指独占而不可被打断）。写的时候可能有执行两个store汇编指令
3.重新安排的语句（也许对于单线程正确，但对多线程却是破坏了预期行为）
  C++标准只要求编译所得的代码在单一线程内的可观测行为是正确的（因为重新安排语句之后，在但一线程内并不在意谁执行前谁执行后，它们毫不相关，但在多线程情况下，它们的前后对第二个线程就有相关性了）
  为什么要重新安排语句：默认情况下C++编译器有能力生成高度优化的代码，而某些优化行为可能需要重新排列语句，而这些要求只针对单线程.


解决问题所需要的性质有哪些？
1.Atomicity（不可切割性）
  意味读或写一个变量或一连串语句，其行为是独占的、排他的，无任何打断的。因此一个线程不可能读到“因另一个线程而造成的”中间状态
2.Order（次序）
  有办法保证“具体指定语句”的次序，C++标准库从高级到低级提供如下概念：
  (1)future and promise，一定在形成成果（返回值或异常）之后才设定shared state，意味读和写不会并发发生
  (2)mutex and lock，处理criticl section or protected zone，借此赋予独占权力
  (3)condition variable，允许一个或多个线程处理其它一个或多个线程所提供的数据或状态
  (4)atomic data type，确保每个变量或对象的访问动作是不可切割的
  (5)atomic data type的底层接口，允许专家放宽atomic语句的次序或对内存访问使用手制栅栏（manual barrier, 即fence）
  

当mutex被用来在一个循环（loop）内读取数据时，为什么通常不要求使用volatile？


多线程遵守哪些原则？
1.多个线程并发处理相同的数据而又不曾同步化，那么唯一安全的情况就是：所有线程只读取数据

线程安全的保证有哪些？
1.并发处理同一容器内不同元素是可以的。即不同的线程可以并发读/写同一容器内的不同元素
2.并发处理string stream, file stream, or stream buffer会导致不可预期的行为


18.5 Mutex和Lock
凡是可能发生concurrent access的地方都该使用同一个mutex，不论读或写都如此。
mutex互斥体，是个object，用来协助采取独占排他方式控制“对资源的并发访问”，相应的线程必须锁定（lock）mutex，这样可防止其他线程也锁定mutex，直到第一个线程解锁（unlock）mutex。

使用mutex时，为了确保异常也能解除（unlock）相应的mutex，应该使用RAII(Resource Acquisition IS Initialization)守则。构造函数获得资源，析构函数释放资源。为了这个目的，C++标准库提供了class std::lock_guard，同时lock应该被限制在可能的最短周期内，就有了{}这个作用域的使用，代码如下：
int val;
{
  std::mutex valMutex;
  std::lock_guard<mutex> lg(valMutex);
  if (val >=0) {
    f(val);
  } else {
    f(-val);
  }
}
 
{
  std::lock_guard<mutext> lg(valMutex);
  ++val;
}

mutex允许同一线程多次锁定，并在最近一次（last）相应的unlock()时释放lock。那就使用：
std::recursive_mutex db_mutex;

std::lock_guard<std::recursive_mutex> lg(db_mutex);

尝试性的Lock以及带时间性的Lock
std::mutex m;
// try to acquire a lock and do other stuff while this isn't possible
while(m.try_lock() == false) {
  doSomethingStuff();
}

// 为了仍能够使用lock_guard(使当下作用域的任何出口都会自动unlock mutex),传额外实参adopt_lock给其构造参数。

std::lock_guard<std::mutext> lg(m, std::adopt_lock);

为了等待特定长度的时间，选用（带时间性的），所谓timed mutex，有两个特殊的mutex
std::timed_mutex std::recursive_timed_mutex,可用以等待时间段或时间点，这对实时需求或避免可能的deadlock或许有帮助。

std::timed_mutex m;
if (m.try_lock_for(std::chrono::seconds(1))) {
  std::lock_gurad<std::timed_mutex> lg(m, std::adopt_lock); // 注意此处仍然使用std::adopt_lock，以区别与std::mutex对象。
}

使用std::adopt_lock的作用是，当前的这个mutex已经被锁定了，但是在离开当下作用域的时候，仍然可以自动unlock mutex。

还可以使用全局函数：std::lock和std::try_lock锁定多个mutex。前者会锁住它收到的所有mutex，而且阻塞直到所有mutex都被锁定或直到抛出异常。如果是抛出异常，已被锁定的mutex都会被解锁。成功锁定后，仍应该使用lock_guard并以adopt_lock作为初始化的第二实参。

后者，若全部锁定返回-1，否则返回第一个失败的lock的索引（从0开始计），且如果这样的话，所有成功的lock会又被unlocked。前者lock次序不定，而后者是按照实参列的次序来尝试完成锁定的。

通常，不会“只调用lock()或try_lock()”却“不把那些lock过继（adopt）给一个lock_guard”。


class unique_lock
它比class lock_guard更加灵活，后者的object生命中总是锁定一个mutex。而unique_lock允许明确写出“何时”以及“如何”锁定或解锁其mutex。可调用owns_lock()或bool()来查询其mutex目前是否被锁定。
它的优点是：析构函时mutex仍然被锁住，其析构函数会自动调用unlock()，若没有锁住mutex，则析构函数什么也不做。

0. std::unique_lock<std::mutex> lock(mutex); // 表示构造时获取锁，也lock_guard一样
它还有三种构造函数：
1. std::unique_lock<std::mutex> lock(mutex, std::try_to_lock);
if (lock) { // if lock was successful
}

2. std::unique_lock<std::timed_mutex> lock(mutex, std::chorono::secondes(1));

3. std::unique_lock<std::mutex> lock(mutex, std::defer_lock); // 表示初始化时并不打算锁住，一般用来建立一个或多个lock并稍后才锁住它们，如下：

std::mutex m1;
std::mutex m2;

std::unique_lock<std::mutex> lock_m1(m1, std::defer_lock);
std::unique_lock<std::mutex> lock_m2(m2, std::defer_lock);
...
std::lock(m1, m2);


任何“带有至少一个write”的并发处理，都应该被同步化。
任何发生在critical section内（也就是某个lock的设立和接触之间），这样的代码不得以“读/写动作被移出critical section之外”的形式被优化。所以不能使用volatile。

对于“某一满足条件”的轮询（polling）通常用mutex不是个好办法，更好的做法是使用condition variable(条件变量)。

mutex不明确行为：
如果程序unlock一个并非它拥有的mutex object，
或销毁(m.~mutex(),必须未被锁定)一个被任何线程拥有的mutex object，
或是线程拥有mutex object但却结束了生命

细说Mutex和Lock
1.有4中Mutex：mutex,recursive_mutex,timed_mutex,recursive_timed_mutex

std::mutex:同一时间只可被一个线程锁定，若它锁定，任何其它lock调用都会阻塞，直到这个mutex再次可用，且try_lock()会失败
std::recursive_mutex:允许在同一个时间多次被同一个线程获得其lock。典型的应用：函数捕获一个lock并调用另一个函数并再次捕获相同的lock
std::timed_mutex:额外允许传递一个时间段或时间点，用来定义多长时间内可尝试捕获一个lock，提供try_lock_for and try_lock_until
std::recursive_timed_mutex:允许同一线程多次获得其lock，可指定期限

lock_guard:用以确保一个locked mutex在离开作用域时总是被释放，在整个生命周期内总是与一个lock关联，要么被申请要么在构造期被接受（std::adopt_lock）
unique_lock:为一个不一定锁定的mutex提供一个lock guard。若在析构期仍锁定mutex会调用unlock，可明确控制是否有一个关联的mutex，是否这个mutex被锁定，可有期限或无期限尝试锁定锁。

只调用一次：
背景：有时候初始化被某个线程使用后，其它线程再也不需要它。典型的例子是：lazy initialization（缓式初始化）第一次某个线程需要某些数据而该数据必须备妥。如某一个布尔值，某一个vector需要初始化。若多个线程检查初始值可能发生data race，C++标准库提供了一个特殊解法：只需使用一个std::once_flag以及调用std::call_once(它也由mutex提供)

只调用一次
std::once_flag和std::call_once。使用方法：
std::once_flag oc;  // global flag，如可定义static
...
// initialize代表可调用对象（callable object），如function,member function, function object or lambda
std::call_once(oc, initialize); // initialize if not initialized yet.
第一个参数是once_flag, 第二个参数是可调用对象。原则上可以使用同一个once flag调用不同的函数，若同一个函数第二次传入相同的once flag，call_once就不会再执行可调用对象。

class X{
  private:
    mutable std::once_flag inti_data_flag;
	void initData() const;
  public:
	data GetData() const {
	  std::call_once(init_data_flag, &X::initData, this);
	  ...
	}
};

在C++中，mutable也是为了突破const的限制而设置的。被mutable修饰的变量，将永远处于可变的状态，即使在一个const函数中。
