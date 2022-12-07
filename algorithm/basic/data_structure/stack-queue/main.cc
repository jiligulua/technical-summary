#include <iostream>
#include <pthread.h>
#include <string>
#include <unistd.h>

int i = 0;

void* test(void *s) {
  int buf[1024];
  std::cout << "i=" << i++ << std::endl;
  test(s);
  return nullptr;
}

class Base {
  public:
	Base() {}
	~Base() {}

	void Initialize() {}
};

class Derived : public Base {
  public:
	Derived() {}
	~Derived() {}

	void run() {
	  if (name_.empty()) {
	    std::cout << "name is invalid" << std::endl;
	  }
	}
  
  private:
    std::string name_;
};

int main() {
  Derived d;
  d.run();
  pthread_t p1, p2;
  std::cout << "tid" << gettid() << std::endl;  
//  pthread_create(&p1, nullptr, test, nullptr);
//  pthread_create(&p2, nullptr, test, nullptr);
  sleep(100);
  return 1;
}
