#include <iostream>
#include <string>
#include <vector>

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

int main() {
  const A a;
  fun(a);
  std::string str(9, 'c');
  std::cout << str << std::endl;

  NoDefault nodefault = 10;
  //std::vector<NoDefault> vec(10);
}
