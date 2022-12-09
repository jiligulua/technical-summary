#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>
#include <array>
#include <string>
#include <memory>

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::array;

template <typename T>
void Print(const T& t) {
  for (const auto& i : t) {
    cout << i << " ";
  }
  cout << endl;
} 

// 41.数据流中的中位数
template <typename T>
class DynamicArray {
 public:
  void Insert(T num) {
    if (((max.size()+min.size()) & 0x1) == 0) { // 偶数
	  if (max.size() > 0 && num < max[0]) {
	    max.push_back(num);
		std::push_heap(max.begin(), max.end(), std::less<T>());

		num = max[0];
		std::pop_heap(max.begin(), max.end(), std::less<T>());
		max.pop_back();
	  }

	  min.push_back(num);
	  std::push_heap(min.begin(), min.end(), std::greater<T>());
	} else { // 奇数情况
      if (min.size() > 0 && num > min[0]) {
	    min.push_back(num);
		std::push_heap(min.begin(), min.end(), std::greater<T>());

		num = min[0];
		std::pop_heap(min.begin(), min.end(), std::greater<T>());
		min.pop_back();
	  }

	  max.push_back(num);
	  std::push_heap(max.begin(), max.end(), std::less<T>());
	}
  }

  T GetMedian() {
    auto count = min.size() + max.size();
	if (count == 0)
	  throw std::runtime_error("There are no evalible element");

	T median = 0;
	if ((count & 0x1) == 1) 
	  median = min[0];
	else
	  median = (min[0] + max[0]) >> 1;

	return median;
  }

 private:
  vector<T> max;
  vector<T> min;
};

// 42.连续子数组的最大和
// 直观法，一般不是最好的方法，之后优先寻找规律，其次使用动态规划
int FindGreatSumOfSubArray(int *pdata, int length) {
  if (nullptr == pdata || length <= 0)
	throw std::invalid_argument("Invalid argument!");

  int cur_sum  = pdata[0];
  int max = cur_sum;
  for (int i = 1; i < length; ++i) {
	int temp = cur_sum + pdata[i];
	cur_sum = pdata[i] > temp ? pdata[i] : temp;
	if (cur_sum > max) 
	  max = cur_sum;
  }

  return max;
}

// 43.1~n整数中1出现的次数

// 45.把数组排成最小的数
void PrintMinNumber(int *numbers, int length) {
  if (nullptr == numbers || length <= 0)
	return;

  vector<string> svec;
  for (int i = 0; i < length; ++i)
	svec.emplace_back(std::to_string(numbers[i]));

  std::sort(svec.begin(), svec.end(), [](string value, string next) -> bool {
			  auto l(value + next);
			  auto r(next + value);
  			  auto result = std::mismatch(l.cbegin(), l.cend(), r.cbegin());
			  if (result.first == l.cend() && result.second == r.end())
			    return false; // 表示维持原顺序，不往前插。
			  else if (*result.first < *result.second)
			    return true; // 当返回为true时，才将value往前插。
			  else 
		        return false; // 表示维持原顺序		  
			});
  
  for (const auto& item : svec)
	cout << item;

  cout << endl;
}

// 递归存在重复子问题，递归是从最大的问题开始自上而下解决问题，可以用递归来分析问题，
// 而解决问题时，可以自下而上来编码解决问题
// 46.把数组排成最小的数,使用递归，效率低下，因为有重复的计算
int TranslateCountCore(const string& str);
int TranslateCount(int number) {
  if (number < 0)
	return 0;

  return TranslateCountCore(std::to_string(number));
}

int TranslateCountCore(const string& str) {
  if (str.size() == 1)
	return 1;
  else if (str.empty())
	return 1;

  auto two_dig = str.substr(0, 2);
  auto num = std::stoi(two_dig, nullptr, 10);
  if (num <= 25)
	return TranslateCountCore(str.substr(1)) + TranslateCountCore(str.substr(2));
  else 
	return TranslateCountCore(str.substr(1));
}

// 46.把数组排成最小的数,不使用递归，效率变高，从下而上
/**
		 |
		 | 1, i = n-1
		 |
		 | 2, i = n-2 && ai,i+1 <= 25
		 | 1, i = n-2 && ai,i+1 > 25
		 |
         | f(i+1)   if [i][i+1] > 25 
  f(i) = | 
         | f(i+1) + f(i+2)  if [i][i+1] <= 25, i+2 <= n-1
		 | 
		 | 
  */
int TranslateCountCoreEx(const string& str);
int TranslateCountEx(int number) {
  if (number < 0)
	return 0;

  return TranslateCountCoreEx(std::to_string(number));
}

int TranslateCountCoreEx(const string& str) {
  int *count = new int[str.size()];
  for (int i = str.size()-1; i >= 0; --i) {
	if (i == str.size()-1) {
	  count[str.size()-1] = 1;
	  continue;
	}

    count[i] = count[i+1];
    int sub_num = std::stoi(str.substr(i, 2), nullptr, 10);
    if (sub_num <= 25) {
      if (i < str.size()-2) 
        count[i] += count[i+2];
  	  else 
  	    count[i] += 1;
  	}
  }

  int cnt = count[0];
  delete[] count;
  return cnt;
}

// 49.丑数
bool IsUgly(int number) {
  while (number % 2 == 0)
	number /= 2;
  
  while (number % 3 == 0) 
	number /= 3;

  while (number % 5 == 0)
	number /= 5;

  return (number == 1) ? true : false;
}

int GetUglyNumber(int index) {
  if (index <= 0)
	return 0;

  int number = 0;
  int number_ugly = 0;
  while (number_ugly < index) {
    ++number;

	if (IsUgly(number))
	  ++number_ugly;
  }

  return number;
}

int Min(int num1, int num2, int num3) {
  int min = (num1 < num2) ? num1 : num2;
  return (min < num3) ? min : num3;
}

int GetUglyNumberEx(int index) {
  if (index <= 0)
	return 0;

  int *ugly = new int[index];
  ugly[0] = 1;
  int next_ugly_index = 1;

  int* pmultipy2 = ugly;
  int* pmultipy3 = ugly;
  int* pmultipy5 = ugly;

  while (next_ugly_index < index) {
    int min = Min(*pmultipy2*2, *pmultipy3*3, *pmultipy5*5);
	ugly[next_ugly_index] = min;

	while (*pmultipy2*2 <= ugly[next_ugly_index])
	  ++pmultipy2;

	while (*pmultipy3*3 <= ugly[next_ugly_index])
	  ++pmultipy3;

	while (*pmultipy5*5 <= ugly[next_ugly_index])
	  ++pmultipy5;

	++next_ugly_index;
  }

  int result = ugly[index-1];
  delete[] ugly;

  return result;
}

int main() {
  // 41. 求中位数
  //DynamicArray<int> dynamic_array;
  //int number;
  //cout << "41.求中位数------------------------------------------" << endl;
  //while (std::cin >> number) 
  //  dynamic_array.Insert(number);

  //cout << "中位数是：" << dynamic_array.GetMedian() << endl;

  //cout << "42.连续子数组的最大和--------------------------------" << endl;
  //int data[] = {1,-2,3,10,-4,7,2,-5};
  //auto max = FindGreatSumOfSubArray(data, sizeof(data)/ sizeof(data[0]));
  //cout << "最大和是：" << max << endl;

  // 45.把数组排成最小的数
  //int num2[] = {3, 32, 321};
  vector<int> ivec = {3,5,4,7,8};
  sort(ivec.begin(), ivec.end(), [](int a, int b) ->bool { 
				  if (a > b)
				    return true;
				  else 
				    return false;
				  
				});
  for (auto i : ivec)
	cout << i << " ";
  cout << endl;


  int num2[] = {3, 30, 34, 5, 9};
  PrintMinNumber(num2, sizeof(num2) / sizeof(int));

  int num3 = 12258;
  cout << num3 << " count " << TranslateCountEx(num3) << endl; 

  cout << "the 1500 ugly number is: " << GetUglyNumberEx(1500) << endl;
}
