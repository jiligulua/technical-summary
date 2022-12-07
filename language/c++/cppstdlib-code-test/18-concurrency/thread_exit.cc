#include <thread>
#include <iostream>
#include <assert.h>
#include <chrono>
#include <future>
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

int main()
{
    // 创建一个 std::promise 对象
    std::promise<void> exitSignal;
    //获取与promise关联的std::future 对象
    std::future<void> futureObj = exitSignal.get_future();
    // 启动线程并且通过引用移动lambda函数中的未来对象
    std::thread th(&threadFunction, std::move(futureObj));
    //等待10秒
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "Asking Thread to Stop" << std::endl;
    //设置promise中的值
    exitSignal.set_value();
    //等待线程加入
    th.join();
    std::cout << "Exiting Main Function" << std::endl;
    return 0;
}
