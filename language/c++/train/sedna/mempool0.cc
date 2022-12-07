#include <iostream>

using std::cout;
using std::cin;

class Rational {
 public:
  Rational(int a = 0, int b = 1) 
    : numberator(a)
	, denominator(b) { }
 
 private:
  int numberator_; // 分子
  int denominator_; // 分母
};

int main() 
{
  Rational *array[1000];
}
