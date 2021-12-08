// Neptune.cpp: 定义应用程序的入口点。
//

#include "Neptune.h"

using namespace std;

#include "Neptune.h"
#include "non_mutate.h"
#include "test_non_mutate.h"
#include "test_array.h"


int partition2(vector<int>& arr, int begin, int end)
{
	int pivot = arr[begin];
	while (begin < end)
	{
		while (begin < end && arr[--end] >= pivot);
		arr[begin] = arr[end];
		while (begin < end && arr[++begin] <= pivot);
		arr[end] = arr[begin];
	}
	arr[begin] = pivot;
	return begin;
}

int partition(vector<int>& arr, int begin, int end) {
	int pivot = arr[begin];
	// Last position where puts the no_larger element.
	int pos = begin;
	for (int i = begin + 1; i != end; i++) {
		if (arr[i] <= pivot) {
			pos++;
			if (i != pos) {
				swap(arr[pos], arr[i]);
			}
		}
	}
	swap(arr[begin], arr[pos]);
	return pos;
}

int main()
{
	vector<int> nums{5, 1, 6, 7, 4};
	int ret = partition2(nums, 0, nums.size());

	test_np_search_n();
	test_np_serach_n_predicat();

	test_multi_array();
	test_multi_array_using();

	system("pause");

	//bool is_bind_expr = is_bind_expression<decltype(f_greater)>::value;

	return 0;
}
