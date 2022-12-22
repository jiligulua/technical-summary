#ifndef PROJECT_VISITOR_H_
#define PROJECT_VISITOR_H_

template <typename... Types>
struct Visitor;

template <typename T, typename... Types>
struct Visitor<T, Types...> : Visitor<Types...> {
  // 通过using避免隐藏基类的Visit同名方法
  using Visitor<Types...>::Visit;
  virtual void Visit(const T&) = 0;
};

template <typename T>
struct Visitor<T> {
  virtual void Visit(const T&) = 0;
};

// Visitor模式的测试代码
#include <iostream>
struct StA;
struct StB;

struct Element {
  typedef Visitor<StA, StB> ConcreteVisitor;
  virtual void Accept(ConcreteVisitor&) = 0;
};

struct StA : Element {
  double val;
  void Accept(Element::ConcreteVisitor& v) {
    v.Visit(*this);
  }
};

struct StB : Element {
  int val;
  void Accept(Element::ConcreteVisitor& v) {
    v.Visit(*this);
  }
};

struct PrintVisitor : Element::ConcreteVisitor {
  void Visit(const StA& a) {
    std::cout << "from StA: " << a.val << std::endl;
  }

  void Visit(const StB& b) {
    std::cout << "from StB: " << b.val << std::endl;
  }
};

#endif //  PROJECT_VISITOR_H_


