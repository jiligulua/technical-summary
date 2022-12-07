#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>

using namespace std;

void doSomething(int num, char c) {
  try {
    default_random_engine dre(42*c);
	uniform_int_distribution<int> id(10, 1000);
	for (int i = 0; i < num; ++i) {
	  this_thread::sleep_for(chrono::milliseconds(id(dre)));
	  cout.put(c).flush();
	}
  } catch(const exception & e) {
    cerr << "Thread-Exception (thread " << this_thread::get_id() << "): "
		 << e.what() << endl;
  } catch(...) {
    cerr << "Thread-Exception (thread " << this_thread::get_id() << ") " << endl;
  }
}

int main() {
  try {
    thread t1(doSomething, 5, '.');
	cout << "- started fg thread " << t1.get_id() << endl;// fg:foreground


	for (int i = 0; i < 5; ++i) {
	  thread t(doSomething, 10, 'a'+i);
	  cout << "- detach started bg thread " << t.get_id() << endl; // bg:background
	  t.detach();
	}

	cout << "- started fg thread concurrency counts " << t1.hardware_concurrency() << endl;// fg:foreground
	cout << "\nMain thread id " << this_thread::get_id() << endl;
	cin.get(); // wait for any input(return)

	cout << "- join fg thread " << t1.get_id() << endl;
	t1.join(); // wati for t1 to finish
  } catch(const exception &e) {
    cerr << "Exception: " << e.what() << endl;
  }
}
 
