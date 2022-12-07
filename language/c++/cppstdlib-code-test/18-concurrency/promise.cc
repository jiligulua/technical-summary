#include <locale>
#include <thread>
#include <future>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <functional>
#include <utility>

using namespace std;


void doSomething(std::promise<std::string> &p) {
  try {
	std::cout << "read char ('x' for exception): ";
	char c = std::cin.get();
	if (c == 'x') {
	  throw std::runtime_error(std::string("char ") + c + " read");
	}

	std::string s = std::string("char ") + c + " processed";
	//p.set_value(std::move(s));
	p.set_value_at_thread_exit(std::move(s));
  } catch(...) {
    //p.set_exception(std::current_exception());
    p.set_exception_at_thread_exit(std::current_exception());
  }
}

int main() {
  try {
    std::promise<std::string> p;
	std::thread t(doSomething, std::ref(p));
	t.detach();

	// create a future to process the outocme
	std::future<std::string> f(p.get_future());

	// process the outcome
	std::cout << "result: " << f.get() << std::endl;
  } catch(const std::exception &e) {
	std::cerr << "EXCEPTION: " <<  e.what() << std::endl;
  } catch(...) {
    std::cerr << "EXCEPTION " << std::endl;
  }
}
