异步操作的主要目的是让调用方法的主线程不需要同步等待调用函数，从而可以让主线程继续执行它下面的代码。因此异步操作无须额外的线程负担，使用回调的方式进行处理。在设计良好的情况下，处理函数可以不必或者减少使用共享变量，减少了死锁的可能。当需要执行I/O操作时，使用异步操作比使用线程+同步 I/O操作更合适。

异步和多线程并不是一个同等关系，异步是目的，多线程是实现异步的一个手段。实现异步可以采用多线程或交给另外的进程来处理。

C++11中的异步操作主要有std::future、std::async、std::promise、std::packaged_task。

1、std::future
        future对象是std::async、std::promise、std::packaged_task的底层对象，用来传递其他线程中操作的数据结果。

函数原型：
#include <future>
template< class T >  class future;
template< class T >  class future<T&>;
template<>        class future<void>;


成员函数：
(构造函数)构造 future 对象 (公开成员函数)
(析构函数)析构 future 对象 (公开成员函数)

operator=:移动future对象 (公开成员函数)
share:从 *this 转移共享状态给 shared_future 并返回它 (公开成员函数)

获取结果：
get:返回结果 (公开成员函数)

状态：
valid:检查 future 是否拥有共享状态(公开成员函数)
wait:等待结果变得可用(公开成员函数)
wait_for: 等待结果，如果在指定的超时间隔后仍然无法得到结果，则返回。(公开成员函数)
wait_until:等待结果，如果在已经到达指定的时间点时仍然无法得到结果，则返回。(公开成员函数)

类模板std::future提供访问异步操作结果的机制：
（1）通过 std::promise、std::packaged_task和std::async创建的异步操作能提供一个 std::future 对象给该异步操作的创建者。
（2）异步操作的创建者能用各种方法查询、等待或从 std::future 提取值。若异步操作仍未提供值，则这些方法可能阻塞。
（3）异步操作准备好发送结果给创建者时，它能通过修改链接到创建者的 std::future 的共享状态（例如 std::promise::set_value ）进行。

注：
std::future 所引用的共享状态不与另一异步返回对象共享（与 std::shared_future 相反）。
std::asyanc是std::future的高级封装， 一般我们不会直接使用std::futrue，而是使用对std::future的高级封装std::async。
例：
#include <iostream>
#include <future>
#include <thread>
 
int main()
{
    // 来自 packaged_task 的 future
    std::packaged_task<int()> task([](){ return 7; }); 		// 包装函数
    std::future<int> f1 = task.get_future();  			// 获取 future
    std::thread(std::move(task)).detach(); 			// 在线程上运行
 
    // 来自 async() 的 future
    std::future<int> f2 = std::async(std::launch::async, [](){ return 8; });
 
    // 来自 promise 的 future
    std::promise<int> p;
    std::future<int> f3 = p.get_future();
    std::thread( [&p]{ p.set_value_at_thread_exit(9); }).detach();
 
    std::cout << "Waiting..." << std::flush;
    f1.wait();
    f2.wait();
    f3.wait();
    std::cout << "Done!\nResults are: "
            << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
 
system("pause");
return 0;
}
result:
Waiting...Done!
Results are: 7 8 9

2、std::async
std::future可以从异步任务中获取结果，一般与std::async配合使用，std::async用于创建异步任务，实际上就是创建一个线程执行相应任务。

std::async就是异步编程的高级封装，封装了std::future的操作，基本上可以代替std::thread 的所有事情

std::async的操作，其实相当于封装了std::promise、std::packaged_task加上std::thread。

函数原型
#include<future>
template< class Function, class... Args >
std::future<std::result_of_t<std::decay_t<Function>(std::decay_t<Args>...)>>
    async( std::launch policy, Function&& f, Args&&... args );

参数：

policy：线程的创建策略：一种是调用即创建线程（std::launch::async）；另一种是延迟加载方式创建线程（std::launch::deferred），调用时不创建线程，直到调用future的get或者wait时才创建线程。
f：线程函数
args：线程函数的参数
返回值：

指代此次调用 std::async 所创建的共享状态的 std::future

例：
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>

std::mutex m;	// 互斥量
struct X {
	void foo(int i, const std::string& str) {
		std::lock_guard<std::mutex> lk(m);
		std::cout << str << ' ' << i << '\n';
	}
	void bar(const std::string& str) {
		std::lock_guard<std::mutex> lk(m);
		std::cout << str << '\n';
	}
	int operator()(int i) {
		std::lock_guard<std::mutex> lk(m);
		std::cout << i << '\n';
		return i + 10;
	}
};

template <typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end)
{
	auto len = end - beg;
	if (len < 1000)
		return std::accumulate(beg, end, 0);

	RandomIt mid = beg + len / 2;
	auto handle = std::async(std::launch::async,parallel_sum<RandomIt>, mid, end);
	int sum = parallel_sum(beg, mid);
	return sum + handle.get();
}

int main()
{
	std::vector<int> v(10000, 1);
	std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';

	X x;
	// 以默认策略调用 x.foo(42, "Hello") ：
	// 可能同时打印 "Hello 42" 或延迟执行
	auto a1 = std::async(&X::foo, &x, 42, "Hello");

	// 以 deferred 策略调用 x.bar("world!")
	// 调用 a2.get() 或 a2.wait() 时打印 "world!"
	auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");

	// 以 async 策略调用 X()(43) ：
	// 同时打印 "43"
	auto a3 = std::async(std::launch::async, X(), 43);
	a2.wait();                     // 打印 "world!"
	std::cout << a3.get() << '\n'; // 打印 "53"

	system("pause");
	return 0;

} // 若 a1 在此点未完成，则 a1 的析构函数在此打印 "Hello 42"

可能结果
The sum is 10000
Hello 42
world!
43

3、std::promise
        std::promise提供了不同线程之间的数据同步机制，可存储一个某种类型的值，并将其传递给对应的future，即使这个future不在同一个线程中也可以访问到这个值。

函数原型：
#include<future>
template< class R > class promise;
template< class R > class promise<R&>;
template<>          class promise<void>;

1) 空模板
2) 非 void 特化，用于在线程间交流对象
3) void 特化，用于交流无状态事件
        每个 promise 与共享状态关联，共享状态含有一些状态信息和可能仍未求值的结果，它求值为值（可能为 void ）或求值为异常。 promise 可以对共享状态做三件事：

使就绪： promise 存储结果或异常于共享状态。标记共享状态为就绪，并解除阻塞任何等待于与该共享状态关联的 future 上的线程。
释放： promise 放弃其对共享状态的引用。若这是最后一个这种引用，则销毁共享状态。除非这是 std::async 所创建的未就绪的共享状态，否则此操作不阻塞。
抛弃： promise 存储以 std::future_errc::broken_promise 为 error_code 的 std::future_error 类型异常，令共享状态为就绪，然后释放它。

promise 是 promise-future 交流通道的“推”端：存储值于共享状态的操作同步于（定义于 std::memory_order ）任何在共享状态上等待的函数（如 std::future::get ）的成功返回。其他情况下对共享状态的共时访问可能冲突：例如， std::shared_future::get 的多个调用方必须全都是只读，或提供外部同步。

成员函数：
(构造函数):构造std::promise对象(公开成员函数)
(析构函数):析构std::promise对象(公开成员函数)
operator=:赋值共享状态(公开成员函数)
swap:交换二个 promise 对象(公开成员函数)

获取结果：
get_future:返回与承诺结果关联的future(公开成员函数)

设置结果：
set_value:设置结果为指定值(公开成员函数)
set_value_at_thread_exit:设置结果为指定值，同时仅在线程退出时分发提醒(公开成员函数)
set_exception:设置结果为指示异常(公开成员函数)
set_exception_at_thread_exit:设置结果为指示异常，同时仅在线程退出时分发提醒(公开成员函数)

非成员函数：
std::swap(std::promise)(C++11)特化 std::swap 算法(函数模板)
辅助类：
std::uses_allocator<std::promise>(C++11):特化 std::uses_allocator 类型特征(类模板特化)

#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>
 
void accumulate(std::vector<int>::iterator first,
	std::vector<int>::iterator last,
	std::promise<int> accumulate_promise)
{
	int sum = std::accumulate(first, last, 0);
	accumulate_promise.set_value(sum);			// 提醒 future
}
 
void do_work(std::promise<void> barrier)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	barrier.set_value();
}
 
int main()
{
	// 演示用 promise<int> 在线程间传递结果。
	std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
	std::promise<int> accumulate_promise;
	std::future<int> accumulate_future = accumulate_promise.get_future();	// 传递其他线程中操作结果
	std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
		std::move(accumulate_promise));
	accumulate_future.wait();	// 等待结果
	std::cout << "result=" << accumulate_future.get() << '\n';
	work_thread.join();			// 阻塞等待线程完成
 
	// 演示用 promise<void> 在线程间对状态发信号
	std::promise<void> barrier;
	std::future<void> barrier_future = barrier.get_future();
	std::thread new_work_thread(do_work, std::move(barrier));
	barrier_future.wait();		// 等待结果
	new_work_thread.join();		// 阻塞等待线程完成
 
	system("pause");
	return 0;
}
结果：
result=21

4、std::packaged_task
std::packaged_task的作用是提供一个不同线程之间的数据同步机制，它可以存储一个函数操作，并将其返回值传递给对应的future，而这个future在另一个线程中也可以安全的访问这个值。

函数原型：
#include<future>
template< class > class packaged_task; // 不定义
template< class R, class ...Args > 
class packaged_task<R(Args...)>;

成员函数：
(构造函数)构造任务对象(公开成员函数)
(析构函数)析构任务对象(公开成员函数)
operator=移动任务对象(公开成员函数)
valid检查任务对象是否拥有合法函数(公开成员函数)
swap交换二个任务对象(公开成员函数)

获取结果：
get_future返回与承诺的结果关联的 std::future(公开成员函数)
		
执行：
operator():执行函数(公开成员函数)
make_ready_at_thread_exit:执行函数，并确保结果仅在一旦当前线程退出时就绪(公开成员函数)
reset:重置状态，抛弃任何先前执行的存储结果 (公开成员函数)
		
非成员函数：
std::swap(std::packaged_task)(C++11)特化 std::swap 算法(函数模板)

帮助类：
std::uses_allocator<std::packaged_task>(C++11)(C++17 前):特化 std::uses_allocator 类型特征 (类模板特化)

#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>
 
// 避免对 std::pow 重载集消歧义的独有函数
int f(int x, int y) { return std::pow(x, y); }
 
void task_lambda()
{
	std::packaged_task<int(int, int)> task([](int a, int b) {
		return std::pow(a, b);
	});
	std::future<int> result = task.get_future();
 
	task(2, 9);
 
	std::cout << "task_lambda:\t" << result.get() << '\n';
}
 
void task_bind()
{
	std::packaged_task<int()> task(std::bind(f, 2, 11));
	std::future<int> result = task.get_future();
 
	task();
 
	std::cout << "task_bind:\t" << result.get() << '\n';
}
 
void task_thread()
{
	std::packaged_task<int(int, int)> task(f);
	std::future<int> result = task.get_future();
 
	std::thread task_td(std::move(task), 2, 10);
	task_td.join();
 
	std::cout << "task_thread:\t" << result.get() << '\n';
}
 
int main()
{
	task_lambda();
	task_bind();
	task_thread();
 
	system("pause");
	return 0;
}
结果：
task_lambda:    512
task_bind:      2048
task_thread:    1024
