#include <future>
#include <thread>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <chrono>
using namespace std;

int queryNumber() {
  cout << "read number: ";
  int num;

  cin >> num;

  if (!cin) {
    throw std::runtime_error("no number read");
  }

  return num;
}


void doSomething(char c, std::shared_future<int> f) {
  try {
    int num = f.get();

	for (int i = 0; i < num; ++i) {
	  this_thread::sleep_for(std::chrono::milliseconds(100));
	  cout.put(c).flush();
	}
  } catch(const std::exception &e) {
    cerr << "Exception in thread " << std::this_thread::get_id()
		 << ": " << e.what() << endl;
  }
}

int main() {
  //auto q = async(launch::async, queryNumber).share();
  shared_future<int> f = async(launch::async, queryNumber);

  auto f1 = async(launch::async, doSomething, '.', f);
  auto f2 = async(launch::async, doSomething, '+', f);
  auto f3 = async(launch::async, doSomething, '*', f);
 
  try {
    f1.get();
    f2.get();
    f3.get();
  } catch(const exception &e) {
    cerr << "\nException: " << e.what() << endl;
  } 

  cout << "\ndone" << endl;
  return 1;
}
