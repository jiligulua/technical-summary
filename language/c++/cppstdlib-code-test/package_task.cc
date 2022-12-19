#include <iostream>
#include <future>
#include <thread>
#include <iostream>
#include <future>
#include <thread>
#include <utility>
#include <exception>

void Worker()

int DoSomething(int num) {
  std::cout << "this thread id is " << std::this_thread::get_id() << std::endl;
  return num;
}

int test() {
  std::packaged_task<int(int)> t;
  std::packaged_task<int(int)> t2(DoSomething);
  std::packaged_task<int(int)> t3(std::move(t2));
  t = std::move(t3);

  std::cout << "t1 is valid ? " << std::boolalpha << t.valid() << std::endl;

  std::future<int> f = t.get_future();

  try {
    t.make_ready_at_thread_exit(1);
    t(1);
	std::cout << "t result is ? " << f.get() << std::endl;

	std::cout << "\ndone" << std::endl;

  } catch (const std::exception& e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  return 1;
}

int main() {
  test();
  std::cout << "Input any char to end" << std::endl;
  std::cin.get();
}
