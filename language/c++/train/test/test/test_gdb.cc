#include <iostream>
#include <condition_variable>
#include <exception>
#include <stdexcept>

struct Person
{
  std::string name;
  int age;
};

std::condition_variable cv;
int g_house_number = 803;

int HaveBreakfast() {
  int milk = 1;
  int soup = 1;
  std::cout << "Have a breakfirst " << "milk: " << milk << " soup: " << soup << std::endl;
  return 1;
}

void GotoKindergarden() {
  Person daughtor { "xiaoxiao", 4};
  std::cout << "name: " << daughtor.name << " age: " << daughtor.age << std::endl;
  int iret = HaveBreakfast();
  std::cout << "<result> for HaveBreakfast: " << iret << std::endl;
}

std::string shcooll_name() {
  return "Shangdi District Primer";
}

void GotoPrimarySchool() {
  Person son { "beibei", 7};

 // throw std::runtime_error("test catch");
  std::cout << "name: " << son.name << " age: " << son.age << std::endl;

}

int main(int argc, char*argv[]) {
  Person dad { "Chris", 14};

  std::cin.get();
  GotoKindergarden();
  GotoPrimarySchool();
  std::cout << "name: " << dad.name << " age: " << dad.age << std::endl;
}
