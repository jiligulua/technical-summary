
c++标准库：
17：数值
产生随机数：分引擎和分布两部分。引擎默认有初始状态，它产生随机值，提供不同的种子，就会产生不同的随机序列。相同的种子或默认状态，产生的随机值序列是相同的。有效种子可以为两次鼠标点击之间的毫秒数或cpu时钟数。std::default_random_engine所产生的随机直依赖于实现，不同平台可能使用算法不同，相同的种子可能产生不同的直（在不同的平台上）。分布可以取常规的均匀分布：std::uniform_int_distribution或std::uniform_real_distribution。随机值取值范围，通过分布来指定。需要小心：不应该传入临时引擎，因为每次初始值一个引擎，其初始状态相同。

若不引入分布，还可以对容器数据通过洗牌方式std::shuffle打乱容器或区间内的元素。引擎所产生的数据为：无正负号整数值。

提供的引擎有：16个，4类，缺省引擎、基础引擎、引擎适配器、适配器并带预定以参数；
提供的分布有：20个，4类，分别是均匀分布、泊松分布、正态分布、抽样分布；

选择那个引擎和分布，由具体实现决定。
引擎可通过stringstream流（内存流）的读写来实现序列化保存。

18：并发
多线程并发访问，标准库已支持并发编程。

介绍各种各样的线程启动方式，介绍高级和底层接口。最主要的问题就是数据的并发（为介词）访问。
同步化线程的特征
并发数据访问的特征

std::future<int> result1(std::async(fun1));
auto result1(std::async(fun1));

int result2 = fun2();

int result = result1.get() + result2;

此时，fun1在后台运行，fun2在前台运行，现在fun1和fun2都是并行运行。
launch策略：强迫async()绝不延迟目标函数的执行

std::future<long> result = std::async(std::launch::async, fun1);
这样就不必🉐调用get()了。
也可以强制延迟执行(deferred)直到调用get()

wait_for&wait_until能让我们写出“投机性运行”
