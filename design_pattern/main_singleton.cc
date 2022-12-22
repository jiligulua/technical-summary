#include <iostream>
#include "singleton.h"
#include <string>

class A {
 public:
  A() {};
  void Test() { std::cout << "Hello World!" << std::endl; }
};

class B {
 public:
  B(const std::string& name) : name_(name) {};
  void Test() { std::cout << "My name is " << name_ << std::endl; }

 private:
  std::string name_;
};

int main() {
  Singleton<A>::Instance();
  Singleton<B>::Instance("Chris");

  Singleton<A>::GetInstance()->Test();
  Singleton<B>::GetInstance()->Test();


  Singleton<B>::DestroyInstance();
  Singleton<A>::DestroyInstance();

  return 1;
}
