#include <iostream>
#include <exception>

int FindRightOneOrder(int num) {
  int index = 0;
  // 这是一种很高效的思维方式，有STL的风格所在。把不能满足的表达式作为while中的条件判断。直到期望的事情发生时，使while循环中的条件为false。
  while (((num & 1) == 0) && (index < 8*sizeof(int))) {
    num = num >> 1;  
	++index;
  }
  return index;
}

bool IsBit1(int data, int right_1_order) {
  data = data >> right_1_order;
  return data & 1;
}

void FindApearOnce(int data[], int length, int* num1, int* num2) {
  if (nullptr == data || length < 2)
    return;

  int result_xor = 0;
  for (int i = 0; i < length; ++i)
    result_xor ^= data[i];

  int right_1_order = FindRightOneOrder(result_xor);

  *num1 = 0;
  *num2 = 0;
  for (int i = 0; i < length; ++i) {
    if (IsBit1(data[i], right_1_order)) 
	  *num1 ^= data[i];
	else
	  *num2 ^= data[i];
  }
}

int FindOnceExcludeTriple(int nums[], int len) {
  if (nullptr == nums || len <= 0)
    throw std::runtime_error("invalid input.");

  // 对每一个数字进行各个位相加，存放在一个32位的数组中，
  // 再对数组中的每个数用3 module
  // 再将所得的数，按照二进制规则转化为一个整数
  // 该数就是所要求得结果
  int every_bit_sum[32] = {0};
  for (int i = 0; i < len; ++i) {
	unsigned int flag = 1;
    for (int j = 31; 0 <= j; --j) {
      if (nums[i] & flag)
	    ++every_bit_sum[j];
	  flag = flag << 1;
	}
  }

  int result = 0;
  for (int i = 0; i < 32; ++i) {
	result = result << 1;
    result += every_bit_sum[i] % 3;
  }

  return result;
}

int main() {
  // 有两个数都是单个，其它数都是双个
  int data[] = {3,3,4, 5, 6,6, 7,7,8,9,8,9};
  int num1, num2;
  FindApearOnce(data, sizeof(data)/sizeof(int), &num1, &num2);
  std::cout << "single numbers are " << num1 << " and " << num2 << std::endl; 

  // 一个数是单个数，其它数都是3个
  int nums[] = {3,3,3,5,4,4,4,8,8,8};
  try {
    int result = FindOnceExcludeTriple(nums, sizeof(nums)/sizeof(int));
    std::cout << result << std::endl;
  } catch(...) {
    std::cout << "Exception!" << std::endl;
  }
}
