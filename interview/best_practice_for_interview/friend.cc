#include <iostream>
using namespace std;

// 模板类声明
template <typename T>
class Test;

// 模板函数声明
template <typename T>
std::ostream& operator<<(std::ostream& os, const Test<T>& obj);

// 模板类定义
template <typename T>
class Test {
 private:
  int num;

 public:
  Test(int n = 0) : num(n) {}
  Test(const Test<T>& rhs) {
    num = rhs.num;
  }

  friend std::ostream& operator<<<T>(std::ostream& os, const Test<T>& obj); // 在“<<”后加上"<>"表明这是个函数模板
};

// 模板函数定义
template <typename T>
std::ostream& operator<<(std::ostream& os, const Test<T>& obj) {
  std::cout << obj.num << std::endl;
  return os;
}

//////////////// test
class Base {
 public:
  void fun(void) { std::cout << "Base::fun" << std::endl; }
};

class Derived : private Base {
 public:
  void fun2(void) { std::cout << "Derived::fun2" << std::endl; }
};

int main() {
  Test<int> t(2);
  std::cout << t << std::endl;

  Derived derived;
  derived.fun2();
  // derived.fun(); // 该函数不能被访问


  return 0;
}
