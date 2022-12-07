#include <iostream>
#include <thread>
#include <future>
#include <exception>
#include <random>

using namespace std;

void doSomething(char c) {
//auto doSomething(char c) -> decltype(std::this_thread::get_id()){
  default_random_engine dre(c);
  //default_random_engine dre(std::chrono::system_clock::now().time_since_epoch().count());
  uniform_int_distribution<int> uid(10, 1000);

  for (int i = 0; i < 10; ++i) {
    this_thread::sleep_for(chrono::milliseconds(uid(dre)));
    
	// test for cout duration
	//auto dur = chrono::milliseconds(uid(dre));
    //this_thread::sleep_for(dur);
	//cout <<  dur.count();
	cout.put(c).flush();
  } 

//  return std::this_thread::get_id();
}

int main() {
  auto f1 = async(std::launch::async, [] { return doSomething('+'); });
  auto f2 = async(std::launch::async, [] { return doSomething('.'); });

    // poll unitil at least one of loops finished
  while (f1.wait_for(chrono::seconds(0)) != future_status::ready && 
	     f2.wait_for(chrono::seconds(0)) != future_status::ready) {
    this_thread::yield();
  }
  
 // auto f1 = async([] { doSomething('+'); });
 // auto f2 = async([] { doSomething('.'); });

 // if (f1.wait_for(chrono::seconds(0)) != future_status::deferred ||
 //     f2.wait_for(chrono::seconds(0)) != future_status::deferred) {
 //   // poll unitil at least one of loops finished
 //   while (f1.wait_for(chrono::seconds(0)) != future_status::ready && 
 //   	   f2.wait_for(chrono::seconds(0)) != future_status::ready) {
 //     this_thread::yield();
 //   }
 // }
  cout.put('\n').flush();

  // wait for all loops to be finished and process any exception

  try {
    f1.get();
	f2.get();
    //cout << f1.get();
	//cout << f2.get();
  } catch(const exception &e) {
    cout << "\nException: " << e.what() << endl;
  }

  cout << "\ndone" << endl;

  return 1;
}
