#include <condition_variable>
#include <mutex>
#include <future>
#include <iostream>

bool ready_flag;
std::mutex ready_mutex;
std::condition_variable ready_condition_variable;

void thread_func1() {
  // do something thread2 needs preparation
  std::cout << "<return>" << std::endl;
  std::cin.get();

  {
    std::lock_guard<std::mutex> lg(ready_mutex);
	ready_flag = true;
  }

  ready_condition_variable.notify_one();
}

void thread_func2() {
  // wait until thread1 is ready(ready_flag is true)
  {
    std::unique_lock<std::mutex> ul(ready_mutex);
	ready_condition_variable.wait(ul, []{ return ready_flag;});
  } // release lock

  // do whatever shall happen after thread1 has prepared things
  std::cout << "done" << std::endl;
}

int main() {
  auto f1 = std::async(std::launch::async, thread_func1);
  auto f2 = std::async(std::launch::async, thread_func2);
}
