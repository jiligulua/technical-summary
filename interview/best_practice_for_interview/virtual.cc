#include <iostream>

using namespace std;

// 若是虚函数继承，则C类只有一个vptr，B类只有一个vptr，A类只有一个vptr，那么，它们的sizeof分别是（64位系统）：16，24，32
// 若还增加虚继承，则每个继承的类保留各自的虚拟指针，在64位系统上sizeof分别是：16，32，48

class A {
  char k[7];
 public:
  virtual void aa() {}
};

class B : public A {
  char j[7];
 public:
  virtual void bb() {}
};

class C : public B {
  char i[7];
 public:
  virtual void cc() {}
};

class AA {
  char k[7];
 public:
  virtual void aa() {}
};

class BB: public virtual AA {
  char j[7];
 public:
  virtual void bb() {}
};

class CC : public virtual BB {
  char i[7];
 public:
  virtual void cc() {}
};

int main(int argc, char* argv[]) {
  cout << "sizeof(A): " << sizeof(A) << endl;
  cout << "sizeof(B): " << sizeof(B) << endl;
  cout << "sizeof(C): " << sizeof(C) << endl;

  cout << "sizeof(AA): " << sizeof(AA) << endl;
  cout << "sizeof(BB): " << sizeof(BB) << endl;
  cout << "sizeof(CC): " << sizeof(CC) << endl;

  cout << "sizeof(int): " << sizeof(int) << endl;

}
