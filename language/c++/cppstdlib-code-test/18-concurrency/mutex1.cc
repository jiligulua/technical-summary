




#include <iostream>
#include <future>
#include <mutex>
#include <string>

std::mutex printMutex;

// 所谓将输出同步化，就是令每次对print的调用都独占地写出所有字符
// lock_guard,在构造函数中加锁，在析构函数中解锁。但是！lock的次序仍旧是不明确的
void print(const std::string& str) {
  std::lock_guard<std::mutex> lg(printMutex);
  for (char c : str) {
    std::cout.put(c);
	//std::this_thread::yield();
  }
  std::cout << std::endl;
}

bool ready_flag = false;
std::mutex ready_flag_mutex;

void thread1_func() {
  // do something thread2 needs as preparation
  // ...
  std::lock_guard<std::mutex> lg(ready_flag_mutex);
  ready_flag = true;
}

void thread2_func() {
  // wait until ready_flag is true(thread1 is done)
  {
    std::unique_lock<std::mutex> ul(ready_flag_mutex);//  此时也是直接锁定互斥体
	while (!ready_flag) {
	  ul.unlock();
	  std::this_thread::yield(); // hint to reschedule to the next thread
	  std::this_thread::sleep_for(std::chrono::milliseconds(100));

	  // sleep_for和yield都可以让当前线程放弃CPU使用权的目的
	  // yield主动让出CPU，并且不参与CPU的本次调度，从而让其它线程有机会运行，在后继的调度周期里再参与CPU调度
	  // sleep_for，同样让出CPU，并且休眠一段时间，从而让其它线程有机会运行。在等待休眠结束时，才参与CPU调度。
	  ul.lock(); 
	}
  } // release lock,将拥有权移交给另一个lock

  // do whatever shall happen after thread1_func has prepared things.
}

int main() {
  auto f1 = std::async(std::launch::async, print, "Hello from the first thread");
  auto f2 = std::async(std::launch::async, print, "Hello from the second thread");
  print("Hello from the main thread");
}

