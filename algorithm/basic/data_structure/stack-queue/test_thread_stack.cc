#include <iostream>
#include <pthread.h>
#include <unistd.h>

int i = 0;

void* test(void *s) {
  int buf[1024];
  std::cout << "i=" << i++ << std::endl;
  test(s);
  return nullptr;
}

int main() {
  pthread_t p1, p2;
  std::cout << "tid" << gettid() << std::endl;  
  pthread_create(&p1, nullptr, test, nullptr);
  pthread_create(&p2, nullptr, test, nullptr);
  sleep(100);
  return 1;
}
