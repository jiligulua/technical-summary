#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

using std::vector;
using std::cout;
using std::endl;

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
int main() {
  // 41. 求中位数
  DynamicArray<int> dynamic_array;
  int number;
  cout << "41.求中位数------------------------------------------" << endl;
  while (std::cin >> number) 
    dynamic_array.Insert(number);

  cout << "中位数是：" << dynamic_array.GetMedian() << endl;

  cout << "42.连续子数组的最大和--------------------------------" << endl;
  int data[] = {1,-2,3,10,-4,7,2,-5};
  auto max = FindGreatSumOfSubArray(data, sizeof(data)/ sizeof(data[0]));
  cout << "最大和是：" << max << endl;
}
