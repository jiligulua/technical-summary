#include <atomic>
#include <chrono>
#include <iterator>
#include <thread>

std::atomic<bool> ready_flag(false);

void thread1() {
  // do something thread2 needs as preparation
  // ...
  ready_flag.store(true);
}

void thread2() {
  // wait until ready_flag is true (thread1 is done)
  while (!ready_flag.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  // do whatever shall happen after thread1 has prepared things
  // 
}


std::atomic<bool> ready_flag;
// ...
std::atomic_init(&ready_flag); // 为了写出C编译器可接受的代码
