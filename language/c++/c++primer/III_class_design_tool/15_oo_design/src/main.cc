#include <iostream>
using std::cout; using std::endl;

#include <utility>

#include <vector>
using std::vector;

#include <memory>
using std::shared_ptr;

#include <algorithm>

#include "quote.h"

class Base {
 public:
  //Base() = default;
  Base() { 
	cout << "Base::Base()" << endl; 
  }
  
  Base(const Base& rhs) { 
  	cout << "Base::Base(const Base& rhs)" << endl; 
  }

  Base(Base&& rhs) noexcept { 
	cout << "Base::Base(Base&& rhs)" << endl; 
  }

  Base& operator=(const Base& rhs) { 
	cout << "Base& operator=(const Base& rhs)" << endl; 
    return *this;
  }

  Base& operator=(Base&& rhs) noexcept { 
	cout << "Base& operator=(Base&& rhs)" << endl; 
    return *this;
  }

  void display() { cout << "Base::display()" << endl; }
  void display(const std::string& str) { cout << "Base::display(const std::string&)" << endl; }
  virtual void func() { std::cout << "Base::func()" << std::endl; }
};

class Derived : public Base {
 public:
  using Base::display;
  Derived() { 
	cout << "Derived::Derived()" << endl; 
  }

  Derived(const Derived& rhs) : Base(rhs) {
    cout << "Derived(const Derived& rhs)" << endl;
  }

  Derived& operator=(const Derived& rhs) {
    cout << "Derived& operator=(const Derived& rhs)" << endl;
    if (this == &rhs)
	  return *this;

	Base::operator=(rhs);
	return *this;
  }

  Derived(Derived&& rhs) : Base(std::move(rhs)) {
	cout << "Derived& operator=(Derived&& rhs)" << endl; 
  }

  void display(int i) { cout << "Derived::display(int)" << endl; }
  void display(const std::string& str)  { cout << "Derived::display(const std::string&)" << endl; }
  void func() override { std::cout << "Derived::func()" << std::endl; }
};

int main() {
  Quote q("C++20", 68);
  BulkQuote bulk_quote("C++17", 58.0, 5, 0.2);

  //DiscQuote d;

  q.Debug();
  bulk_quote.Debug();

  Derived derived;
  Derived d2(derived);
  Derived d3(std::move(d2));

  Base* base = &derived;
  base->func();

  base->display();

  derived.display();
  derived.display("Hello World");
  
  vector<shared_ptr<Quote>> quotes;
  quotes.push_back(std::make_shared<BulkQuote>("C++ Primer", 58, 10, 0.1));
  quotes.push_back(std::make_shared<Quote>("Modern Effective C++", 58));

  cout << "---------------" << endl;

  for (auto item : quotes)
	cout << item->net_price(20) << endl;
  
}
