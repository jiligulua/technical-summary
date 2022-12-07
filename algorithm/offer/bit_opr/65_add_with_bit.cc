#include <iostream>

int Add(int num1, int num2) {
  // 基于两个数的bit进行加法运算，即二进制加法运算
  // 1.先进行各个bit相加，不考虑进位
  // 2.凡是需要进位的，都是1，那就与一下，就可以得到所有需要进位的位置，整体左移一位就是进位，即一个数据
  // 3.重复1和2，直到进位值为0
  
  int carry = 0;
  int sum = 0;
  do {
    sum = num1 ^ num2;
	carry = (num1 & num2) << 1;
	num1 = sum;
	num2 = carry;
  } while (num2 != 0);

  return sum;
}

int main() {
  std::cout << "Test Add with bit" << std::endl;
  int num1, num2;
  while (true) {
    std::cout << "Input num1 and num2: ";
    if (std::cin >> num1 >> num2) {
	  std::cout << "result: " << Add(num1, num2) << std::endl;
    } else {
	  std::cout << "Input invalid, end add" << std::endl;
	  break;
	}
  }
  
}
