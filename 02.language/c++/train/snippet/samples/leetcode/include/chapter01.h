#pragma once
#include "base.h"

namespace npt
{
    void test_chapter01();

	int singleNumber(vector<int> &nums);
    int majorityElement(vector<int> &nums);
    int majorityElement2(vector<int> &nums);


    void quick_sort(vector<int> &arr, int begin, int end);
    int partition_hoare(vector<int>& arr, int begin, int end);
    int partition_lomuto(vector<int>& arr, int begin, int end);
    


}