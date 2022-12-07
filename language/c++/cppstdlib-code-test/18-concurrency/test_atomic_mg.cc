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
#include <atomic>
#include <cstdlib>
#include <future>
#include <memory>
#include <thread>
#include <chrono>
#include <iostream>

long data;
std::atomic<bool> ready_flag(false);

void Provider() {
  // after reading a character
  std::cout << "<return>" << std::endl;
  std::cin.get();

  // provider some data
  data = 42;

  // and signal readiness
  ready_flag.store(true); // Provider提供若干数据，使用store表示数据已提供。
  // store()会对影响所及的内存区执行一个所谓的release操作，确保此前所有内存操作不论是否为atomic，在store返回作用之前都变成“可被其他线程看见”
}

void Consumer() {
  // wait for readiness and do something else
  while (!ready_flag.load()) { // 不断执行load，然后处理data
    std::cout.put('.').flush(); // 这样就知道了，等待了多个次
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  // and process provided data
  std::cout << "\nvalue: " << data << std::endl; // 原子操作是为并发操作而提供的工具，为了是告诉编译器本函数内不改变次序，同时确保了在原子操作前后，数据的变化是可以避免data race的。因为原子操作的boolalpha可以确保原子读写，有它控制的操作或数据就有保证了。
}

// 所有atomic操作默认使用一个特别的内存次序，名为std::memory_order_seq_cst，它代表sequential consistent memory order(顺序一致的内存次序)。底层的atomic操作能够放宽这一次序保证。

// 具体是：由于data的设值发生在provider将ready_flag存储为true之前，而对data的处理发生在consumer将true载入放进ready_flag之后，因此对data的处理保证发生在data

int main() {
  // start provider and consumer
  auto p = std::async(std::launch::async, Provider);
  auto c = std::async(std::launch::async, Consumer);
  std::atomic<int> a(1);

  int pre_add = ++a;
  std::cout << "\npre_add" << pre_add << std::endl;
  int post_add = a++;
  std::cout << "\npost_add" << post_add << "a value is " << a <<std::endl;

}
