#include <iostream>
#include <string>
#include <vector>
#include "mylib.h"

class Screen;
class A {
 public:
  std::string str(const Screen& s) const;

 private:
  std::string str_;
};

class Screen {
  friend class A;
  friend std::string A::str(const Screen&) const;
  using pos = std::string::size_type;

  pos r;
  pos c;
  std::string content;
};

std::string A::str(const Screen& s) const { 
  std::cout << s.r << " " << s.c << std::endl;
  return str_; 
}

void fun(const A& a) {
  Screen s;
  a.str(s);
}

class NoDefault {
 public:
  NoDefault(int i) : i_(i) {}

 private:
  int i_;
};

class Debug {
 public:
  constexpr Debug(bool b = true) : hw_(b), io_(b), other_(b) {}
  constexpr Debug(bool h, bool i, bool o) : hw_(h), io_(i), other_(o) {}
  constexpr bool any() { return hw_ || io_ || other_; }


 private:
  bool hw_;
  bool io_;
  bool other_;
};

class Example {
 public:
  static double rate;
  static std::vector<double> vec;
};

std::vector<double> Example::vec(4);

int main() {
  const A a;
  fun(a);
  std::string str(9, 'c');
  std::cout << str << std::endl;

  mylib_fun();

  NoDefault nodefault = 10;
  //std::vector<NoDefault> vec(10);
  Example e;
  std::cout << "size of Example::vec is " << Example::vec.size() << std::endl;;
}
