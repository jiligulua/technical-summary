#include <iostream>
using std::cout; using std::endl;

#include "quote.h"

class Base {
 public:
  void display() { cout << "Base::display()" << endl; }
  void display(const std::string& str) { cout << "Base::display(const std::string&)" << endl; }
  virtual void func() { std::cout << "Base::func()" << std::endl; }
};

class Derived : public Base {
 public:
  using Base::display;
  void display(int i) { cout << "Derived::display(int)" << endl; }
  void display(const std::string& str) { cout << "Derived::display(const std::string&)" << endl; }
  void func() override { std::cout << "Derived::func()" << std::endl; }
};

int main() {
  Quote q("C++20", 68);
  BulkQuote bulk_quote("C++17", 58.0, 5, 0.2);

  //DiscQuote d;

  q.Debug();
  bulk_quote.Debug();

  Derived derived;
  Base* base = &derived;
  base->func();

  base->display();

  derived.display();
  derived.display("Hello World");
}
