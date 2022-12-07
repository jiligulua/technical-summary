#include <memory>
#include <iostream>

class Tester {
  public:
    int name;
  
	 
};

void OutputResult(std::unique_ptr<int> q) {
  std::cout << *q << std::endl;
}

int main() {
  std::unique_ptr<int> u1(new int(10));
  OutputResult(std::move(u1));
}
