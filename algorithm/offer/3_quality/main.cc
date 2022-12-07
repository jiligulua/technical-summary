#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>
#include <stdexcept>
#include <exception>
#include <cstring>
#include "common.h"

using namespace std;

double PowerWithUnsignedExponent(double base, unsigned int exponent); 
double Power(double base, int exponent) {
  if (base <= 0.0000001 && -0.0000001 <= base && exponent == -1)
	throw std::invalid_argument("Invalid argument.");

 int new_exponent = exponent < 0 ? -exponent : exponent;
 double result = PowerWithUnsignedExponent(base, new_exponent);
 
 return exponent < 0 ? 1.0/result : result;
}

double PowerWithUnsignedExponent(double base, unsigned int exponent) {
  double result = 1.0;
  
  for (int i = 0; i < exponent; ++i)
    result *= base;
  
  return result;
}

double PowerWithUnsignedExponentOp(double base, unsigned int exponent) {
  if (exponent == 0)
    return 1;
  else if (exponent == 1)
    return base;
  else {
    double result = PowerWithUnsignedExponentOp(base, exponent>>1);
	
	result *= result;
	if ((exponent & 0x1) == 1)
	  result *= base;

	return result;
  }
}

int StrToInt(const char* str) {
  if (nullptr == str ||
	  *str == '\0' || 
	 ((*str == '+' || *str == '-') && *(str+1) == '\0' ))
    throw std::invalid_argument("Invalid argument");

  const char* p = nullptr;
  long long result = 0;
  int index = 0;
  bool minus = false;

  if (*str == '-') {
    p = str+1;
	minus = true;
  } else if (*str == '+') {
    p = str+1;
  } 

  while (*p != '\0') {
    if ('0' <= *p && *p <= '9') {
	  result = result * 10 + minus * (*p - '0');
	  ++p;

	  if (!minus && result >= 0x7fffffff) 
	    throw std::overflow_error("Overflow error");
	  else if (minus && result < 0x80000000)
        throw std::underflow_error("Underflow error");
	} else {
	    throw std::invalid_argument("Invalid argument");		
	}
  } 

  return static_cast<int>(result); 
}

// 17
bool Increment(char* number); 
void PrintNumber(char* number); 
void Print1ToN(int n) {
  if (n <= 0)
	return;
  
  char* number = new char[n+1];
  memset(number, '0', n);
  number[n] = '\0';

  while (!Increment(number))
	PrintNumber(number);

  delete[] number;
}

bool Increment(char* number) {
  bool overflow = false;
  int sum = 0;
  int len = strlen(number);
  int carry_flag = 0;

  for (int i = len-1; i >= 0; --i) {
    sum = number[i] - '0' + carry_flag;
	if (i == len-1)
	  ++sum;

	if (sum >= 10) {
	  if (i == 0)
		overflow = true;
	  else {
	    carry_flag = 1;
		number[i] = '0';
	  }
	} else {
	  number[i] = '0' + sum;
	  break;
	}
  }

  return overflow;
}

void PrintNumber(char* number) {
  while (*number == '0')
    ++number;

  printf("%s\n", number);
}

void Print1ToNDigitsRecursively(char* number,  int index, int length);
void Print1ToNDigits(int n) {
  if (n <= 0)
	return;

  char* number = new char[n+1];
  memset(number, '0', n);
  number[n] = '\0';

  for (int i = 0; i < 10; ++i) {
    number[0] = '0' + i;
	Print1ToNDigitsRecursively(number, 1, n);
  }
}

void Print1ToNDigitsRecursively(char* number,  int index, int length) {
  if (index == length) {
	PrintNumber(number);
    return;
  }

  for (int i = 0; i < 10; ++i) {
    number[index] = '0' + i;
	Print1ToNDigitsRecursively(number, index+1, length);
  }
}

// 两个大整数相加的情况
// 1. 数据结构，数组，类型char；2.考虑正负好，++，--和+-的情况；3.负面测试：异常输入
class BigIntegerAdd {
 public:
   enum ComResult {FirstGreat, Equal, FirstLess};

   BigIntegerAdd(char* number1, char* number2) {}
   std::string GetResult() { return ""; }

 private:
   char* number1;
   char* number2;
};

bool IsFirstBigger(char* number1, char* number2);
void AddWithoutSign(char* number1, char *number2, char*& result) {
  if (*number1 == '+' || *number1 == '-')
	number1 += 1;

  if (*number2 == '+' || *number2 == '-')
	number2 += 1;

  bool first_bigger = IsFirstBigger(number1, number2);
  int upper_len = first_bigger ? strlen(number1) : strlen(number2);
  int lower_len = first_bigger ? strlen(number2) : strlen(number1);
  char* upper = first_bigger ? number1 : number2;
  char* lower = first_bigger ? number2 : number1;

  int mx = strlen(upper);
  int mn = strlen(lower);

  int sum = 0;
  int carry = 0;
  result = new char[mx+2];
  memset(result, '0', mx+1);
  result[mx+1] = '\0';

  int result_index = mx;
  int small_index = mn-1;
  for (int i = mx-1, j = mn-1; i >= mx-mn; --i, --j) {
    sum = upper[i] - '0' + lower[j] - '0' + carry;
    if (sum >= 10) {
      carry = 1;
      sum -= 10;
    } else {
      carry = 0;
    }
    result[result_index--] = '0' + sum;
  }
  
  for (int i = mx-mn-1; i >= 0; --i) {
    sum = upper[i] - '0' + carry;
	if (sum >= 10) {
	  sum -= 10;
	  carry = 1;
	} else {
	  carry = 0;
	}
	result[result_index--] = '0' + sum;
  }
  
  if (carry == 1)
	result[result_index] = '0' + 1;
}

bool IsFirstBigger(char* number1, char* number2) {
  int len1 = strlen(number1);
  int len2 = strlen(number2);
  if (len1 > len2)
	return true;
  else if (len1 < len2)
	return false;
  else {
    while (*number1 != '\0' && *number1 == *number2) {
	  ++number1;
	  ++number2;
	}

	return *number1 > *number2 ? true : false;
  }
}

// TODO:
void BiggerFirstSubSecondWithoutSign(char* number1, char *number2, char* result) {}

bool InvalidNumber(char* number) {
  return nullptr == number || 
	  '\0' == *number ||
	  ((*number == '+' || *number == '-') && *(number+1) == '\0');
}

// TODO:
bool FirstBiggerThanSecondWithoutSign(char* number1, char* number2) { return false; }

bool IsPositive(char* number) {
  return (*number != '-') ? true : false;
}

bool IsDiff(char* number1, char* number2) {
  return (IsPositive(number1) && !IsPositive(number2)) || 
		 (!IsPositive(number1) && IsPositive(number2));
}

void AddWithBigInteger(char* number1, char* number2, char*& result) {
  if (InvalidNumber(number1) || InvalidNumber(number2))
	throw invalid_argument("Invalid argument");
  
  // 获取第一个数据的符号和第二个数据的符号，以及两个数据的结果，是正数还负数，
  // 若是++、--关系，则去掉符号之后，进行两个数相加，并在结果处添加符号，若是都是正数，可不添加符号
  // 若是+-关系，判断出除去符号之后，两个数大小，并进行大数-小数。若大数为正号，则结果为正；若大数是负号，则结果为负；
  bool result_is_positive = false; 
  if (IsDiff(number1, number2)) {
    if (FirstBiggerThanSecondWithoutSign(number1, number2)) {
	  BiggerFirstSubSecondWithoutSign(number1, number2, result); 
	  result_is_positive = IsPositive(number1) ? true : false;
	} else {
	  BiggerFirstSubSecondWithoutSign(number2, number1, result);
	  result_is_positive = IsPositive(number2) ? true : false;
	}
  } else {
    AddWithoutSign(number1, number2, result);    
	result_is_positive = IsPositive(number1) ? true : false;
  }
  
  if (!result_is_positive) 
    *result = '-';
}

// 18.正则表达式匹配, 巧用递归，每次都做一步，那么就可以用循环或递归的形式，递归和判断是一体的
bool MatchCore(char* str, char* pattern);
bool match(char* str, char* pattern) {
  if (str == nullptr || pattern == nullptr)
	return false;

  return MatchCore(str, pattern);
}

bool MatchCore(char* str, char* pattern) {
  if (*str == '\0' && *pattern == '\0')
    return true;

  if (*str != '\0' && *pattern == '\0')
	return false;

  // 以下就是pattern至少有两个字符，那么，就可以展开考虑了
  if (*(pattern+1) == '*') { // 表示*所在的地方，可以重复出现0个、1个、2个等
    if (*pattern == *str || (*pattern == '.' && *str != '\0')) { // they are the same meaning.
	  return MatchCore(str, pattern+2) || // *:表示前面的字符出现0次 eg: bac b*bac
			 MatchCore(str+1, pattern+2) || // *:表示前面的字符出现1次 eg: befg b*efg
			 MatchCore(str+1, pattern); // *:表示前面的字符出现1次或多次 eg: bbefg b*efg 
	} else {
	  return MatchCore(str, pattern+2); // eg:b*cac  cac 
	}
  } else {
    if (*pattern == *str || (*pattern == '.' && *str != '\0'))
	  return MatchCore(str+1, pattern+1);
	else
	  return false;
  }
}

// 20.表示数值的字符串, 按顺序扫描，若扫描到最后，不是结尾的话，说明出现了叉子。
// 考查双指针的用法，移动，已经const char* str的含义，已经&str的意义。
bool ScanInteger(const char** str);
bool ScanUnsignedInteger(const char** str);
bool IsNumeric(const char* str) { // 指针指向const char，说明不能更改字符串中的内容
  if (nullptr == str)
	return false;

  bool numeric = ScanInteger(&str);
  if (*str == '.') {
    ++str;
	numeric = ScanUnsignedInteger(&str) || numeric;
  }

  if (*str == 'e' || *str == 'E') {
    ++str;
	numeric = numeric && ScanInteger(&str);
  }

  return numeric && *str == '\0';
}

bool ScanInteger(const char** str) {
  if (**str == '+' || **str == '-')
    ++(*str);

  return ScanUnsignedInteger(str);
}

bool ScanUnsignedInteger(const char** str) {
  const char* head = *str;
  while (**str != '\0' && **str >= '0' && **str <= '9')
    ++(*str);

  return *str > head;
}

// 21.调整数组顺序使奇数位于偶数前面
bool Odd(int i) {
  return (i & 0x1) == 1;
}

void Reorder(int* data, unsigned len, std::function<bool(int)> f) {
  if (nullptr == data || len <= 0)
	throw std::invalid_argument("Reorder function with invalid argument");

  int left = 0;
  int right = len-1;
  while (left < right) {
    while (f(data[left]))
	  ++left;

	while (!f(data[right]))
	  --right;

	if (left < right) {
	  auto temp = data[left];
	  data[left] = data[right];
	  data[right] = temp;
	}
  } 
}

// 23. 链表中环的入口节点
struct ListNode {
  int value;
  ListNode *next;
};

ListNode* MeetingNode(ListNode* head);
ListNode* EntryNodeOfLoop(ListNode* head) {
  ListNode* meeting_node = MeetingNode(head);
  if (nullptr == meeting_node)
	return nullptr;

  int nodes_in_loop = 1;
  ListNode* cur = meeting_node;
  while (cur->next != meeting_node) {
    cur = cur->next;
	++nodes_in_loop;
  }

  cur = head;
  for (int i = 0; i < nodes_in_loop; ++i)
    cur = cur->next;

  ListNode* behind = head;
  while (behind != cur) {
    behind = behind->next;
	cur = cur->next;
  }

  return cur;
}

ListNode* MeetingNode(ListNode* head) {
  if (nullptr == head)
	return nullptr;

  ListNode* slow = head->next;
  if (nullptr == slow)
	return nullptr;

  ListNode* fast = slow->next;
  
  while (fast != nullptr && slow->next != nullptr) {
    if (fast == slow)
	  return fast;

    slow = slow->next;
	fast = fast->next;
	if (fast != nullptr)
	  fast = fast->next;
  }

  return nullptr;
}

int main() {
  cout << "sizeof(int): " << sizeof(int) << endl;
  cout << "sizeof(long long): " << sizeof(long long) << endl;
  array<int, 8> iarr;
  iarr.fill(1);
  //Print(iarr);

  //Print1ToNDigits(3);

  char* result = nullptr;
  char num1[] = "1234567891234567";
  char num2[] = "2222222222222222";
  AddWithBigInteger(num1, num2, result);
  printf("%s + %s = ?\n", num1, num2);
  PrintNumber(result);
  delete[] result;

  const char *str = "123635345243.12324345e12324";
  auto flag = IsNumeric(str);
  cout << str << (flag ? " is numeric" : " is not numeric") << endl;

  cout << "modify the array to odd before even" << endl;
  int iarr2[] = {1,2,3,4,5,6,7,8,9,0,13,14};
  try {
    Reorder(nullptr, 0, nullptr);
  } catch (const std::exception& e) {
    std::cout << "Exception: " << e.what() << endl;
  }
  Reorder(iarr2, sizeof(iarr2)/sizeof(iarr2[0]), Odd);
  for (auto i : iarr2)
	cout << i << " ";
  cout << endl;
}
