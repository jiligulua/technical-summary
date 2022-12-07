atomic的高层接口（也称normal或strong接口）默认保证顺序一致性，就是在线程中atomic操作保证一定“像代码出现的次序”执行指令。
atomic的底层即口（也称weak或relaxed接口）带有“放宽之次序保证”的操作。

注意我总是应该将atomic object初始化，因为其default构造函数并不完全初始化它（不是初始值不明确，而是其lock未初始化）

如果只使用default构造函数，接下来唯一允许的操作是如下调用 global atomic_init():

std::atomic<bool> ready_flag;
...
std::atomic_init(&ready_flag, false);
这种方式是为了写出C编译器可接受的代码

处理stomic的两个重要函数是：store()和load(),前者赋予一个新值，后者取当前值。它们都保证是atomic（不可分割的），所以可以不象以前那样“需要mutex的保护才能够设置ready_flag”。所以第一线程不用这么写：
{
  std::lock_guard<std::mutex> lg(ready_mutex);
  ready_flag = true;
}
而是简单写成这样：
  ready_flag.store(true)

然而，使用condition variable时仍然需要mutex才能保护对condition variable的消费
{
  std::unique_lock<std::mutex> l(ready_mutex);
  ready_condvar.wait(l, []{return ready_flag.load();});
}

对于atomic类型，可继续使用有用而寻常的操作，像是赋值、自动转换为整型、递增、递减等。
std::atomic<bool> ab(false);
ab = true;
if (ab) {
  // ...
}
std::atomic<int> ai(0);
int x = ai; // 这是一个稍微的差异。返回的是被赋予值，而不是返回一个reference指向atomic。
ai = 0;
ai++;
ai-=17;

18.7.2 细说atomic及其高级接口
Default构造函数并未能够完全将object初始化，之后只有调用atomic_init()完成初始化。
接受相关类型值的那个构造函数并不是atomic
所有函数，处理构造函数，都被重载为volatile和non-volatile两个版本

借由is_lock_free()可以检查atomic类型内部是否由于使用lock才成为atomic。若内部不使用lock便返回true。若果返回false，即不是，我的硬件就是拥有对atomic操作的固有支持。

compare_exchange_strong() and compare_exchange_weak()都是所谓compare-and-swap(CAS)操作，CPU常常提供这个atomic操作用以比较“某内存区内容”和“某给定值”，并且唯有在它们相同时才将内存区内容更新为另一个给定的新值。这个可保证新值乃根据最新信息计算出来。因此，如果数值在这一段时间内被另一个线程更新，它会返回false并以expected承载新值。

weak形式有可能出现假失败，即期望值出现仍返回false，但有时候比strong形式更高效。

P1017

18.7.3 Atomic的C-Style接口
C-style接口一般只用于“需要C和C++之间保持兼容”的代码上，然而在C++中使用C-style atomic类型并不罕见。

18.7.4 Atomic的底层接口
Atomic的底层接口意味着使用atomic操作时，不保证顺序一致性。因此，编译器和硬件有可能（局部）重排对atomic的次序。

再请小心：需要很多专家经验才能直到何时值地在内存重排上花心力——即便是专家对此也常常犯错。

atomic底层操作为常用操作：store, load, exchage, CAS, and fetch等操作提供一个增补能力，允许额外传递一个内存次序实参。
a.store(val, mo)
a.load(mo)
a.exchange(val, mo)
a.compare_exchange_strong(exp, des, mo)
a.compare_exchange_strong(exp, des, mo1, mo2)
a.compare_exchange_weak(exp, des, mo)
a.compare_exchange_weak(exp, des, mo1, mo2)
a.fetch_add(val, mo)
a.fetch_sub(val, mo)
a.fetch_and(val, mo)
a.fetch_or(val, mo)
a.fetch_xor(val, mo)

另有若干函数被额外提出来，用以手动控制内存访问，如：atomic_thread_fence() and atomic_signal_fence()被用来手动编写fence，那是“内存访问重安排”的界线。

atomic的底层接口是为真正的并发专家或想成为专家的人准备的，一个良好的出发点是Anthony Williams的著作C++ Concurrency in Action，尤其是第5和第7章。另一个起点是Hans Boehm的一系列URL，都是关于内存模型的文章（见Boehm：C++ MM）
