#include <iostream>
#include <future>
#include <thread>
using namespace std;

int doSomething(int num) {
  cout << "thread id is " << this_thread::get_id() << endl;

  return num;
}

int main() {
  std::packaged_task<int(int)> t1;
  std::packaged_task<int(int)> t2(doSomething);
  std::packaged_task<int(int)> t3(std::move(t2));
  t1 = std::move(t3);
  cout << "t1 is valid? " << boolalpha << t1.valid() << endl;

  std::future<int> f = t1.get_future();

  try {
	//t1(1);
	t1.make_ready_at_thread_exit(1);

    cout << "t1 result is? " << f.get() << endl;

	cout << "\ndone" << endl;
    //cin.get();
  } catch(const exception &e) {
    cout << "Exception " << e.what() << endl;
  }
  return 1;
}
