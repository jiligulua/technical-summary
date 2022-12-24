#include <iostream>
#include <stdexcept>
#include <cstring>
/////////////test
struct Test {
  Test(int) {}
  Test() {};
  void fun() {}
};

//////////test
struct Base {
  Base() { std::cout << "Base::Base()" << std::endl; }
  ~Base() { std::cout << "Base::~Base()" << std::endl;}
};

struct Derived : Base {
  Derived() { std::cout << "Derived::Derived()" << std::endl; }
  ~Derived() { std::cout << "Derived::~Derived()" << std::endl; }
};

///////// test 
class B {
 public:
  B() { std::cout << "default construct" << std::endl; }
  B(int i) : data(i) { std::cout << "constructed by parameter" << data << std::endl; }
  ~B() { std::cout << "destructed" << std::endl; }
 private:
  int data;
};

B play(B b) {
 std::cout << "enter play" << std::endl;
 return b;
}

////////// test 
class A {
public:
  const int size = 0;
};

////////// test

class MyString {
 public:
  MyString(const char* str = nullptr) {
    if (str == nullptr) {
	  str_ = new char[1];
	  *str_ = '\0';
	} else {
	  str_ = new char[strlen(str)+1];
	  strcpy(str_, str);
	}
  }

  MyString(const MyString& rhs) {
	char* temp = new (std::nothrow) char[strlen(rhs.str_)+1];
	if (nullptr == temp) {
	  throw std::runtime_error("Lack of memory");
	} else {
	  strcpy(temp, rhs.str_);
	  delete[] str_;
	  str_ = temp;
	}
  }

  MyString& operator=(const MyString& rhs) {
    if (this == &rhs)
	  return *this;

	char* temp = new (std::nothrow) char[strlen(rhs.str_)+1];
	if (nullptr == temp) {
	  throw std::runtime_error("Lack of memory");
	} else {
	  strcpy(temp, rhs.str_);
	  delete[] str_;
	  str_ = temp;
	}
	return *this;
  }

  MyString& operator+(const MyString& rhs) {
    return *this;
  }

  ~MyString() {
    delete[] str_;
  }

 private:
  char* str_;
};

int main(int argc, char* argv[]) {
  Test test(1);
  test.fun();
 
  {
	Derived d;
  }

  //Test b();
  //b.fun();
  A a;
  std::cout << a.size << std::endl;

  std::cout << "Test B play output" << std::endl;
  //B b = play(5);
  play(5);

//  const MyString s1("Hello");
//  MyString s2(s1);

  char pello[] = "helloworld";
  char qello[] = "qhelloworld";
  MyString s7(pello);
  MyString s8(pello);
  MyString s9(qello);
  s9 = s7 + s8;
}
