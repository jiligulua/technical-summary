#include <iostream>
#include <functional>
#include "events.h"

struct StA {
  int a, b;
  void print(int a, int b) {
    std::cout << __func__ << a << " " << b << " " << std::endl;
  }
};

void print(int a, int b) {
  std::cout << __func__ << a << " " << b << " " << std::endl;
}

int main() {
  Events<std::function<void(int, int)>> events;
  auto key = events.Connect(print); // 以函数方式注册观察者

  auto key_lambda = events.Connect([](int a, int b) {
				  std::cout << __func__ << a << " " << b << std::endl;
				  }); // lambda注册

  StA sta;
  std::function<void(int, int)> f = std::bind(&StA::print, &sta, std::placeholders::_1, std::placeholders::_2);
  events.Connect(f);

  int a = 1, b = 2;
  //events.Notify();
  events.Notify(a, b);
  
  events.Disconnect(key);
}
