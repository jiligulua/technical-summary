18.6 condition variable(条件变量)
并发操作实现同步化的需求有哪些？
1.data race
2.不同线程执行的task必须彼此等待
  future的主要目的是处理线程的返回值或异常
  而condition variable可用来同步化线程之间的数据流逻辑依赖关系

针对目标条件而轮询，请使用条件变量。C++标准库<condition_variable>中提供了一个变量，借由它，一个线程可以唤醒（wake up）一个或多个其它等待中的线程（waiting thread）（等待中的线程不占用CPU资源）

condition variable 的wait成员函数是这么被使用的：你把mutex ready_mutex的lock ul当作第一实参，把一个lambda当作第二实参，用来检测条件是否真的满足。其效果是wait()内部会不断调用该第二实参，直到它返回true。condition variable也许有所谓假醒（即cv的wait动作可能在该cv尚未被notified时便返回），wait内部的循环使用第二个实参直到它返回true，明显是为了处理假醒。同时，wait的第一个参数必须使用unique_lock()，不可使用lock_guard()，因为wait() 内部会明确地对mutex进行解锁和锁定。


18.6.3使用condition variable（条件变量）实现多线程Queue
global queue被并发使用，它被一个mutex和一个condition variable保护着。其中mutex确保读和写是atomic，而condition variable用来“有新元素可用”时激发和唤醒另一个线程。

如果有多个consumer必须处理相同数据，也可调用notify_all()。典型的例子是事件驱动系统，其事件（event）必须被发布给所有曾经登录的consumer，也提供给你一个接口允许你等待某个最大时间量：wait_for()用来等待一个时间段和wait_until()用来等待直到某个时间点。

condition_variable:由C++标准提供，用来唤醒一或多个等待特定条件（是指必须由他人提供或执行的东西）获得满足的线程。多个线程可等待同一条件发生，一旦条件满足，线程就可以通知（notify）所有（或某个）等待线程。

由于发生假醒，当条件满足后仅仅通知是不够的，等待着（线程）还必须在苏醒之后两次检查该条件。

所有通知都会被自动同步化，所以并发调用notify_one和notify_all不会带来麻烦，所有等待某一个条件变量的线程必须使用相同的mutex；当wait()家族的某个成员被调用时该mutex必须被unique_lock锁定，否则会发生不明确的行为。

condition variable消费者总是在“被锁定的mutex”基础上操作。只有等待函数会执行以下三个atomic步骤暂时解除mutex：
1）解除mutex然后进入等待状态；
2）解除因等待而造成的阻塞；
3）再次锁住mutex；

也就意味着传给wait函数的那个判断式总是在lock情况下被调用，所以它们可以安全的处理受mutex保护的对象。

wait_for() and wait_until()
各有一个不接受判断式的版本，它们返回值都属于枚举类：
std::cv_status::timeout:如果发生不容置疑的超时
std::cv_status::no_timeout:如果发生通知

各有一个接受判断式的版本，它们返回值是判断式的执行结果

全局函数notify_all_at_thread_exit(cv,ul)用来在其调用者（线程）退场（exit）时调用notify_all()。为此它暂时锁定对应的lock ul（为什么？因为它要执行清理工作，直到清理工作结束之后，再解锁，以便等待线程获得锁之后可以获得通知信号）。ul必须使用所有等待线程共享的同一个mutex。为避免死锁（deallock），线程调用notify_all_at_thread_exit()之后应该直接退场。因此这个调用只是为了在通知等待线程之前完成清理工作，而且这个清理工作绝不该造成阻塞。

condition_variable_any不要求使用std::unique_lock对象当做lock。即使用的lock不是标准的mutex类型，或使用标准mutex类型的一个unique_lock wrapper，并搭配condition_variable_any，那么使用者必须确保conditon_varaible_any对象所关联的判断式的任何必要同步化，提供同步化的lock() and unlock()成员函数。
一个典型例子可用来激发（signal）“detach thread结束”信号。借由使用notify_all_at_thread_exit()，我可以确保主程序（或者说主线程）处理“detached thread 终止”事实之前，thread local object已被销毁。这个方法真好！

