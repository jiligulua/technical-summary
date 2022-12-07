#include <condition_variable>
#include <mutex>
#include <future>
#include <thread>
#include <iostream>
#include <queue>

std::queue<int> queue;
std::mutex queue_mutex;
std::condition_variable queue_cond_var;

void Provider(int val) {
  // push different values(val til val +5 with timeouts of val milliseconds into the queue)
  for (int i=0; i<6; ++i) {
    {
      std::lock_guard<std::mutex> lg(queue_mutex);
	  queue.push(val+i);
	} // release lock
	//queue_cond_var.notify_one();
	queue_cond_var.notify_all();

	// 通知完之后，休眠一段时间，让其它线程有时间消费数据
	std::this_thread::sleep_for(std::chrono::milliseconds(val));
  }
}

void Consumer(int num) {
  // pop values if available (num identifies the consumer)
  while(true) {
    int val;
	{
	  std::unique_lock<std::mutex> ul(queue_mutex);
	  queue_cond_var.wait(ul, []{ return !queue.empty(); });
	  val = queue.front();
	  queue.pop();
	} // release lock
	std::cout << "consumer " << num << ": " << val << std::endl;
  }
}

int main() {
  // start three providers for values 100+, 300+, and 500+
  auto p1 = std::async(std::launch::async, Provider, 100);
  auto p2 = std::async(std::launch::async, Provider, 300);
  auto p3 = std::async(std::launch::async, Provider, 500);

  // start two consumers printing the values
  auto c1 = std::async(std::launch::async, Consumer, 1);
  auto c2 = std::async(std::launch::async, Consumer, 2);

  try {
    c1.get();
    c2.get();
  } catch(...) {
    std::cout << "Exception!" << std::endl;
  }
  std::cout << "\ndone" << std::endl;
}
