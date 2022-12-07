#include <iostream>
#include <string>

template <typename T> 
void Print(const T &t) {
  for (auto i : t) 
    std::cout << i << " ";
  std::cout << std::endl;
}

template<>
void Print(const std::string &str) {
  std::cout << str << std::endl;
}

template <typename Iter>
void Print(Iter beg, const Iter & end) {
  while (beg != end) 
    std::cout << *beg++ << " ";
  
  std::cout << std::endl;
}

void Tips(const std::string & str) {
  std::cout << "Test " << str << std::endl;
}
