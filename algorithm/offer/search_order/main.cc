#include <stdexcept>
#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <string>
#include <array>
#include <climits>
#include <set>

#include "common.h"

// 手写快排算法
int Partition(int data[], int length, int start, int end) {
  if (nullptr == data || length <= 0 || start < 0 || length <= end)
	throw std::logic_error("Invalid parameter.");


  std::default_random_engine dre(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> uid(start, end);
  int index = uid(dre);
  std::swap(data[index], data[end]);
  int small = start-1;
  for (index = start; index != end; ++index) {
    if (data[index] < data[end]) {
	  ++small;
	  if (small != index) 
	    std::swap(data[small], data[index]);
	}
  }

  ++small;
  std::swap(data[small], data[end]);

  return small;
}

void QuickSort(int data[], int length, int start, int end) {
  if (start == end) 
    return;

  int index = Partition(data, length, start, end);
  if (start < index) 
	QuickSort(data, length, start, index-1);

  if (index < end) 
	QuickSort(data, length, index+1, end);
}

// 实现一个排序算法，要求时间效率位O(n)
void SortAge(int age[], int length) {
  Tips(__func__);
  if (nullptr == age || length <= 0)
    return;

  const int oldest_age = 99;
  int count_of_age[oldest_age+1] = {0};
  for (int i = 0; i < length; ++i) {
    if (age[i] < 0 || age[i] > oldest_age) 
	  throw std::logic_error("Invalid age.");

	++count_of_age[age[i]];
  }

  int index = 0;
  for (int i = 0; i <= oldest_age; ++i) {
    for (int j = 0; j < count_of_age[i]; ++j) 
	  age[index++] = i;
  }
}

// 11.旋转数组的最小数字
int MinInOrder(int data[], int start, int end) {
  int result = data[start];
  for(int i = start+1; i <= end; ++i)  // 完全遍历一边
    if (result > data[i])
	  result = data[i];

  return result;
}

int Min(int data[], int length) {
  Tips(__func__);
  if (nullptr == data || length <= 0)
    throw std::logic_error("Invalid parameter.");

  int min_index = 0;
  int start = 0;
  int end = length-1;
  while (start <= end) {
    if (end - start == 1) {
	  min_index = end;
	  break;
	} else {
	  int mid = ((end - start) >> 1) + start;
      if (data[mid] == data[start] && data[start] == data[end])
		return MinInOrder(data, start, end);

	  if (data[mid] <= data[end]) 
	    end = mid;
	  else if (data[start] <= data[mid]) 
		start = mid;
	}
  }

  return data[end];
}

//在排序数组中查找数字----------
//1.数字在排序数组中出现的次数
int GetFirstK(int data[], int length, int k, int start, int end) {
  if (nullptr == data || length <= 0 || start < 0 || length <= end)
    throw std::logic_error("Invalid Parameter.");
 
  int mid = -1;
  while (start <= end) {
    mid = ((end - start) >> 1) + start;
	int mid_data = data[mid];
    if (mid_data > k) 
	  end = mid-1;
    else if (mid_data < k)
	  start = mid+1;
    else {
	  if ((mid > 0 && data[mid-1] != k) || mid == 0)
	    break;
	  else
	    end = mid-1;
	}	
  }

  return (start > end) ? -1 : mid;
}

int GetLastK(int data[], int length, int k, int start, int end) {
  if (nullptr == data || length <= 0 || start < 0 || length <= end)
    throw std::logic_error("Invalid Parameter.");

  int mid = -1;
  while (start <= end) {
    mid = ((end - start) >> 1) + start;
    int mid_data = data[mid];
	if (mid_data > k)
	  end = mid-1;
	else if (mid_data < k)
	  start = mid+1;
	else {
	  if ((mid < length-1 && data[mid+1] != k ) || mid == length-1)
	    break;
	  else
	    start = mid+1;
	}
  }

  return (start > end) ? -1 : mid;
}

int GetNumberOfK(int data[], int length, int k) {
  Tips(__func__);
  int number = 0;
  
  if (nullptr != data && length > 0) {
    int first = GetFirstK(data, length, k, 0, length-1);
    int last = GetLastK(data, length, k, 0, length-1);
    if (first != -1 && last != -1)
	  number = last - first + 1;
  }

  return number;
}

// 2.0~n-1中缺失的数字
int FindMissingNumber(int data[], int length) {
  Tips(__func__);
  if (nullptr == data || length < 0)
    throw std::logic_error("Invalid Parameter");

  int start = 0;
  int end = length-1;
  int mid = -1;
  while (start <= end) {
    mid = ((end-start) >> 1) + start;
	int mid_data = data[mid];
	if (mid_data == mid) 
	  start = mid+1;
	else {
	  if ((mid>0 && data[mid-1] == mid-1) || mid == 0)
	    break;
	  else
		end = mid-1;
	}
  }

  return (start>end) ? -1 : mid;
}

// 3.数组中数值和小标相等的元素
int GetSameItemAsIndex(int data[], int length) {
  if (nullptr == data || length <= 0)
    return -1;

  int left = 0;
  int right = length-1;
  while (left <= right) {
    int mid = left + ((right-left) >> 1);
	if (data[mid] == mid)
	  return mid;
	else if (data[mid] > mid) 
	  right = mid-1;
	else 
	  left = mid+1;
  }

  return -1;
}

// 50.第一个只出现一次的字符
// 1.字符串中第一个只出现一次的字符
char GetFirstOnlyOneChar(const std::string &str) {
  Tips(__func__);

  if (str.empty())
    return '\0';

  constexpr int TotalCharCounts = 256;
  std::array<int, TotalCharCounts> ca = {0};

  for (auto c : str)
	++ca[c];

  auto it = std::find(ca.cbegin(), ca.cend(), 1);
  if (it != ca.cend())
    return static_cast<char>(it-ca.cbegin());
  else
	return '\0';
}

// extentive question
void RemoveCharBySecond(std::string &str, const std::string &exclude) {
  Tips(__func__);
  if (str.empty() || exclude.empty())
    return;

  std::array<bool, 256> ia = {false};
  for (const auto& i : exclude)
    ia.at(i) = true;

  std::string result;
  for (const auto&  c : str)
    if (!ia.at(c))
	  result.push_back(c);

  std::swap(result, str);
}

void RemoveDuplicate(std::string &str) {
  if (str.empty())
	return;

  Tips(__func__);
  std::array<bool, 256> ba = {false};

  std::string result;
  for (auto c : str) {
    if (!ba.at(c)) {
	  ba.at(c) = true;
	  result.push_back(c);
	}
  }
  std::swap(str, result);
}

bool IsAnagram(const std::string &left, const std::string &right) {
  std::array<int, 256> ia = {0};
  for (const auto& i : left)
    ++ia.at(i);

  for (const auto& i : right)
    --ia.at(i);

  auto it = std::find_if_not(ia.cbegin(), ia.cend(), [](int i) { return i == 0;});
  
  return it == ia.cend();
}

// 题目二：字符流中第一个只出现一次的字符
char GetTheFirstOnlyOneChar(const std::string &str) {
  Tips(__func__);
  std::array<int, 256> iarr;
  iarr.fill(-1);

  char c;
  int index = -1;
  for (auto c : str) {
	++index;
	auto & item = iarr.at(c);
    if (item == -1) {
	  item = index;
	} else if (item >= 0) {
      item = -2;  
	}
  }

  int min = INT_MAX;
  index = -1;
  char result = '\0';
  for (auto i : iarr) {
	++index;
    if (i > 0) 
	  if (i < min) {
	    min = i;
	    result = static_cast<char>(index);
	  }
  }
  return result;
}

// 面试题39：数组中出现次数超过一半的数字
// 解法1：partition算法
int MoreThanHalfNum(int number[], int length) {
  Tips(__func__);
  if (nullptr == number || length <= 0)
	throw std::invalid_argument("Invalid argument");

  int middle = length >> 1;
  int left = 0;
  int right = length-1;
  int index = Partition(number, length, left, right);
  while (index != middle) {
    if (index > middle)  
	  right = index-1;
	else 
	  left = index+1;

	index = Partition(number, length, left, right);
  }

  int result = number[index];

  int cnt = std::count(number, number+length, result);
  if (cnt > middle) 
	return result;
  else
	throw std::logic_error("Invalid array content");
}

// 解法2：使用加减法
int MoreThanHalfNum2(int number[], int length) {
  Tips(__func__);
  if (nullptr == number ||length <= 0)
    throw std::invalid_argument("Invalid argument.");

  int result = number[0];
  int count = 1;
  for (int i = 1; i < length; ++i) {
    if (number[i] == result) {
	  ++count;
	} else if (count > 0) {
	  --count;
	} else {
	  result = number[i];
	  count = 1;
	}
  }
  
  int cnt = std::count(number, number+length, result);
  if (cnt > length >> 1) 
	return result;
  else
	throw std::logic_error("Invalid array content");
}

// 40.最小的K个数
// modify the data
void GetLeastNumber(int* input, int n, int* output, int k) {
  if (nullptr == input || nullptr == output || n <= 0 || k <= 0 || n < k)
    return;

  int left = 0;
  int right = n-1;
  int index = Partition(input, n, left, right);
  while (index != k-1) {
    if (index > k-1) {
	  right = index-1;
	  index = Partition(input, n, left, right);
	} else {
	  left = index+1;
	  index = Partition(input, n, left, right);
	}
  }

  for (int i = 0; i < k; ++i)
	output[i] = input[i];
}

typedef std::multiset<int, std::greater<int>> GreatSet;

void GetLeastNumber2(const std::vector<int>& data, GreatSet& col, int k) {
  if (data.empty() || k < 0 || data.size() < k)
	return;

  for (auto iter = data.cbegin(); iter != data.cend(); ++iter) {
    if (col.size() < k)
      col.insert(*iter);
    else {
	  auto beg = col.begin();
	  if (*iter < *beg) {
	    col.erase(beg);
		col.insert(*iter);
	  } 
	}
  }
}

int main() {
  int data[] = {10, 6, 4, 6, 7, 12, 10, 5, 9};
  Print(data);
  int length = sizeof(data)/sizeof(data[0]);
  int index = Partition(data, length, 0, length-1);
  std::cout << "partition point is " << data[index] << std::endl;
  Print(data);
 
  QuickSort(data, length, 0, length-1);
  Print(data);

  std::cout << std::endl;
  int ages[] = {0, 1, 5, 13, 42, 42, 32, 33, 36, 35, 20,20, 18, 26, 99, 98, 50};
  Print(ages);
  SortAge(ages, sizeof(ages)/sizeof(ages[0]));
  Print(ages);

  //int data2[] = {5,6,7,8,9,10, 2,3,4};
  //int data2[] = {5,6,7,8,9,10, 2,3,4};
  int data2[] = {5,5,5,5,3,3,4,5};
  std::cout << Min(data2, sizeof(data2)/sizeof(data2[0])) << std::endl;

  int data3[] = {1,2,3,3,4,5};
  std::cout << GetNumberOfK(data3, sizeof(data3)/sizeof(data3[0]), 6) << std::endl;

  int data4[] = {0};
  std::cout << FindMissingNumber(data4, sizeof(data4)/sizeof(data4[0])) << std::endl;
  
  int data5[] = {0,1,2,3,5,6,7,8,9};
  std::cout << FindMissingNumber(data5, sizeof(data5)/sizeof(data5[0])) << std::endl;

  //std::string str("abaccedff");
  //std::string str("abcdefghijklmn");
  std::string str("aabbccddeeff");
  Print(str);
  auto first_only_one_char = GetFirstOnlyOneChar(str);
  std::cout << "The first char is: " << first_only_one_char << std::endl;
  
  std::string first_str("We are students");
  std::string second_str("aeiou");
  RemoveCharBySecond(first_str, second_str);
  Print(first_str);

  std::string google("google");
  RemoveDuplicate(google);
  std::cout << google << std::endl;
  
  std::string str1("google"), str2( "elgoog");
  std::cout << "Is Anagram: " << std::boolalpha << IsAnagram(str1, str2) << std::endl;
  
  auto c = GetTheFirstOnlyOneChar("google");
  std::cout << "The first only one char: " << c << std::endl;
  
  int number2[] = {1,2,3,2,2,2,5,4,2};
  try {
    std::cout << "Number is: " << MoreThanHalfNum(number2, sizeof(number2)/ sizeof(number2[0])) << std::endl;
    std::cout << "Number is: " << MoreThanHalfNum2(number2, sizeof(number2)/ sizeof(number2[0])) << std::endl;
  } catch (const std::logic_error& e) {
    std::cout << "Exception: " << e.what() << std::endl;
  } catch (...) {
    std::cout << "Exception for MoreThanHalfNum(2)" << std::endl;
  }


  int data6[] {4,5,1,6,2,7,3,8};
  Print(data6);
  int dst[8] = {0};
  GetLeastNumber(data6, sizeof(data6)/sizeof(data6[0]), dst, 4);
  Print(dst);
  std::vector<int> ivec2 {4,5,1,6,2,7,3,8};
  GreatSet great_set;
  GetLeastNumber2(ivec2, great_set,4);
  Print(great_set);
                                                                                                                                    

}

