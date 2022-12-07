C++11——多线程编程1
2、函数对象
3、Lambda函数

新线程将在创建新对象后立即开始，并且将与已启动的线程并行执行传递的回调。
此外，任何线程可以通过在该线程的对象上调用join()函数来等待另一个线程退出。

看一个主线程创建单独线程的例子，创建完新的线程后，主线程将打印一些信息并等待新创建的线程退出。

函数指针
#include <iostream>
#include <thread>

void thread_function() {
    for (int i = 0; i < 100; i++)
        std::cout << "thread function excuting" << std::endl;
}

int main() {
    std::thread threadObj(thread_function);
    for (int i = 0; i < 100; i++)
        std::cout << "Display from MainThread" << std::endl;
    threadObj.join();
    std::cout << "Exit of Main function" << std::endl;
    return 0;
}
 
函数对象

函数对象创建线程:
#include <iostream>
#include <thread>

class DisplayThread {
public:
    void operator ()() {
        for (int i = 0; i < 100; i++)
            std::cout << "Display Thread Excecuting" << std::endl;
    }
};

int main() {
    std::thread threadObj((DisplayThread()));
    for (int i = 0; i < 100; i++)
        std::cout << "Display From Main Thread " << std::endl;
    std::cout << "Waiting For Thread to complete" << std::endl;
    threadObj.join();
    std::cout << "Exiting from Main Thread" << std::endl;

    return 0;
}
线程间的区分

每个std::thread对象都有一个相关联的id，可以获取到
std::thread::get_id() ：成员函数中给出对应线程对象的id
std::this_thread::get_id() ： 给出当前线程的id
如果std::thread对象没有关联的线程，get_id()将返回默认构造的std::thread::id对象：“not any thread”
std::thread::id也可以表示id
#include <iostream>
#include <thread>

void thread_function() {
    std::cout << "inside thread :: ID = " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::thread threadObj1(thread_function);
    std::thread threadObj2(thread_function);

    if (threadObj1.get_id() != threadObj2.get_id()) {
        std::cout << "Both Threads have different IDs" << std::endl;
    }
    std::cout << "From Main Thread :: ID of Thread 1 = " << threadObj1.get_id() << std::endl;
    std::cout << "From Main Thread :: ID of Thread 2 = " << threadObj2.get_id() << std::endl;

    threadObj1.join();
    threadObj2.join();
    std::cout << "From Main Thread :: ID of Main" << std::this_thread::get_id();
    return 0;
}

----------------------------------------------------------------
C++11——多线程编程2
Joining线程
线程一旦启动，另一个线程可以通过调用std::thread对象上调用join()函数等待这个线程执行完毕
std::thread th(funcPtr);
th.join();
 
看一个例子
主线程启动10个工作线程，启动完毕后，main函数等待他们执行完毕，joining完所有线程后，main函数继续执行

#include <iostream>  
#include <thread>  
#include <algorithm>  
#include <vector>
#include <functional>
class WorkerThread
{
public:
    void operator()() {
        std::cout << "Worker Thread " << std::this_thread::get_id() << "is Excecuting" << std::endl;
    }
};

int main() {
    std::vector<std::thread> threadList;
    for (int i = 0; i < 10; i++) {
        threadList.push_back(std::thread(WorkerThread()));
    }
    // Now wait for all the worker thread to finish i.e.  
    // Call join() function on each of the std::thread object  
    std::cout << "Wait for all the worker thread to finish" << std::endl;
    std::for_each(threadList.begin(), threadList.end(), std::mem_fn(&std::thread::join));
    std::cout << "Exiting from Main Thread" << std::endl;

    return 0;
}

Detaching 线程
detach一个线程，需要在std::thread对象中调用std::detach()函数

std::thread th(funcPtr)
th.detach();
调用detach()后，std::thread对象不再与实际执行线程相关联

在线程句柄上调用detach() 和 join()要小心

case1：不要在没有关联执行线程的std::thread对象上调用join() 或 detach()
std::thread threadObj(WorkerThread());
threadObj.join();
threadObj.join();// It will cause Program to Terminate
当join()函数在线程对象上执行,当join()返回时，std::thread 对象与他没有关联线程，如果在这样的对象上再次调用join()函数，那么它将导致程序终止。
类似的，调用detach()使std::thread对象没有链接任何线程函数，在这种情况下，在一个std::thread对象上调用detach()函数两次将导致程序终止。

std::thread threadObj(WorkerThread);
threadObj.detach();
threadObj.detach();// It will cause Program to Terminate
因此，在每次调用join()或detach()前，需要检查线程是否join-able

std::thread threadObj(WorkerThread())
if (threadObj.joinable()) {
    std::cout << "Detaching Thread" << std::endl;
    threadObj.detach();
}
if (threadObj.joinable()) {
    std::cout << "Detaching Thread" << std::endl;
    threadObj.detach();
}

std::thread threadObj2(WorkerThread())
if (threadObj2.joinable()) {
    std::cout << "Joining Thread" << std::endl;
    threadObj2.join();
}
if (threadObj2.joinable()) {
    std::cout << "Joining Thread" << std::endl;
    threadObj2.join();
}
如果std::thread关联的执行线程没有调用join和detach，那么在对象的析构期，它将终止程序

因为在析构期，它将检查线程是否仍然Join-able，然后终止程序

#include <iostream>
#include <thread>
#include <algorithm>

class WorkerThread
{
public:
    void operator()()
    {
        std::cout << "Worker Thread" << std::endl;
    }
};


int main()
{
    std::thread threadObj((WorkerThread()));
    //如果没有在std::thread对象上调用join或detach，其析构函数将会终止程序
    return 0;
}

类似的，不能忘记在异常情况下调用join或detach

joinable()函数是一个布尔类型的函数，他会返回一个布尔值来表示当前的线程是否有可执行线程(能被join或者detach)，因为相同的线程不能join两次，也不能join完再detach，同理也不能detach，所以joinable函数就是用来判断当前这个线程是否有可以joinable的。通常不能被joinable有以下几种情况：

1）由thread的缺省构造函数而造成的（thread()没有参数）。
2）该thread被move过（包括move构造和move赋值）。
3）该线程被join或者detach过。

----------------------------------------------------------------
C++11多线程编程3
要将参数传递给线程的可关联对象或函数，只需将参数传递给std::thread构造函数。

默认情况下，所有的参数都将复制到新线程的内部存储中。
#include <iostream>
#include <string>
#include <thread>
void threadCallback(int x, std::string str)
{
    std::cout << "Passed Number = " << x << std::endl;
    std::cout << "Passed String = " << str << std::endl;
}
int main()
{
    int x = 10;
    std::string str = "Sample String";
    std::thread threadObj(threadCallback, x, str);
    threadObj.join();
    return 0;
} 

不要将变量的地址从本地堆栈传递给线程的回调函数。因为线程 1 中的局部变量可能已经销毁，但线程 2 仍在尝试通过其地址访问它。
在这种情况下，访问无效地址可能会导致意外行为

#include <iostream>
#include <thread>
void newThreadCallback(int* p)
{
    std::cout << "Inside Thread :  "" : p = " << p << std::endl;
    std::chrono::milliseconds dura(1000);
    std::this_thread::sleep_for(dura);
    *p = 19;
}
void startNewThread()
{
    int i = 10;
    std::cout << "Inside Main Thread :  "" : i = " << i << std::endl;
    std::thread t(newThreadCallback, &i);
    t.detach();
    std::cout << "Inside Main Thread :  "" : i = " << i << std::endl;
}
int main()
{
    startNewThread();
    std::chrono::milliseconds dura(2000);
    std::this_thread::sleep_for(dura);
    return 0;
}

同样的，在传递指向堆内存的指针给heap时，因为某些线程可能在新线程尝试访问它之前删除该内存。在这种情况下，访问无效地址可能会导致不可预测的行为。

#include <iostream>
#include <thread>
void newThreadCallback(int* p)
{
    std::cout << "Inside Thread :  "" : p = " << p << std::endl;
    std::chrono::milliseconds dura(1000);
    std::this_thread::sleep_for(dura);
    *p = 19;
    std::cout << *p << std::endl;
}
void startNewThread()
{
    int* p = new int();
    *p = 10;
    std::cout << "Inside Main Thread :  "" : *p = " << *p << std::endl;
    std::thread t(newThreadCallback, p);
    t.detach();
    delete p;
    p = NULL;
}
int main()
{
    startNewThread();
    std::chrono::milliseconds dura(2000);
    std::this_thread::sleep_for(dura);
    return 0;
}
给线程传递引用。由于参数被复制到新的线程堆栈，所以，如果想通过常用的方式传递引用，如：

#include <iostream>
#include <thread>

void threadCallback(int const& x) {
    int& y = const_cast<int&>(x);
    y++;
    std::cout << "Inside Thread x = " << x << std::endl;
}

int main() {
    int x = 9;
    std::cout << "In Main Thread : Before Thread Start x = " << x << std::endl;
    std::thread threadObj(threadCallback, x);
    threadObj.join();
    std::cout << "In Main Thread : After Thread Joins x = " << x << std::endl;
    return 0;
}
 即使threadCallback接受参数作为引用，但是并没有改变main中x的值，在线程引用外它是不可见的。这是因为线程函数threadCallback中的x是引用复制在新线程的堆栈中的临时值。

如何修改：使用 std::ref

#include <iostream>
#include <thread>

void threadCallback(int const& x) {
    int& y = const_cast<int&>(x);
    y++;
    std::cout << "Inside Thread x = " << x << std::endl;
}

int main() {
    int x = 9;
    std::cout << "In Main Thread : Before Thread Start x = " << x << std::endl;
    std::thread threadObj(threadCallback, std::ref(x));
    threadObj.join();
    std::cout << "In Main Thread : After Thread Joins x = " << x << std::endl;
    return 0;
}
指定一个类的成员函数的指针作为线程函数将指针传递给成员函数作为回调函数，并将指针指向对象作为第二个参数

#include <iostream>
#include <thread>
class DummyClass {
public:
    DummyClass()
    {}
    DummyClass(const DummyClass& obj)
    {}
    void sampleMemberFunction(int x)
    {
        std::cout << "Inside sampleMemberFunction " << x << std::endl;
    }
};
int main() {

    DummyClass dummyObj;
    int x = 10;
    std::thread threadObj(&DummyClass::sampleMemberFunction, &dummyObj, x);
    threadObj.join();
    return 0;
}

----------------------------------------------------------------


----------------------------------------------------------------
----------------------------------------------------------------
函数模板std :: mem_fn生成指向成员的指针的包装对象，该对象可以存储，复制和调用指向成员的指针。 调用std :: mem_fn时，可以使用对象的引用和指针（包括智能指针）。

#include <functional>
#include <iostream>

struct Foo {
    void display_greeting() {
        std::cout << "Hello, world.\n";
    }
    void display_number(int i) {
        std::cout << "number: " << i << '\n';
    }
    int data = 7;
};

int main() {
    Foo f;

    auto greet = std::mem_fn(&Foo::display_greeting);
    greet(f);

    auto print_num = std::mem_fn(&Foo::display_number);
    print_num(f, 42);

    auto access_data = std::mem_fn(&Foo::data);
    std::cout << "data: " << access_data(f) << '\n';
}


C++11——多线程编程16 如何停止或终止线程？

在本文中，我们将讨论如何在 C++11 中停止或终止线程。

C++11 没有提供停止正在运行的线程的直接方法，这是因为该线程可能有一些资源在退出前释放或关闭，即

如果一个线程获得了一个锁，我们突然杀死了那个线程，那么谁来释放那个锁呢？
如果一个线程打开了一个文件来写入文本，而我们停止了该线程，那么谁会关闭该文件呢？
如果线程已经在堆上分配了内存并且在它可以删除该内存之前，我们会停止该线程。那么谁来防止内存泄漏。
因此没有直接关闭线程的函数。但是我们可以通知线程退出，我们可以以这样一种方式实现 out 线程，即在一段时间后或在某些检查点后，它应该检查是否要求我退出。如果是，那么它应该通过释放所有资源优雅地退出。


使用 std::future<> 停止线程
我们可以将std::future<void>对象传递给线程，当未来的值可用时，线程应该退出。因为，我们只想给线程发信号，而不是在该信号中实际传递任何值，所以我们可以使用 void 类型的未来对象。

让我们在 main 函数中创建一个 void 类型的 promise 对象，即
// 创建一个 std::promise 对象
std::promise < void > exitSignal;
 
现在，从主函数中的这个承诺中获取关联的未来对象，即
//获取与promise关联的std::future对象
std::future < void > futureObj = exitSignal.get_future () ;
 
现在在创建线程的主函数中，将未来对象传递给线程函数，即
// 启动线程并通过引用移动 lambda 函数中的未来对象
std::thread th ( &threadFunction, std:: move ( futureObj )) ;

在线程内部，我们正在做一些工作并继续检查线程是否已被请求退出，即未来的值是否可用。

void threadFunction(std::future<void> futureObj)
{
    std::cout << "Thread Start" << std::endl;
    while (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
    {
        std::cout << "Doing Some Work" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "Thread End" << std::endl;
}
一旦我们从 main 函数中设置了 promise 对象的值，未来对象中的值将在线程函数中可用，即

//设置promise中的值
exitSignal.set_value();
