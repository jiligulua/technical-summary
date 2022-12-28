#include <iostream>

using std::cout;
using std::endl;

class Base {
 public:
  virtual void fun() { cout << "Base fun" << endl; }
  virtual ~Base() { cout << "Base::~Base()" << endl; }
};

class Derived : public Base {
 public:
  virtual void fun() { cout << "Derived fun" << endl; }
  virtual ~Derived() { cout << "Derived::~Derived()" << endl; }
};

int main() {
  Derived *p = new Derived();
  Base* pbase = p;
  delete pbase;

}
