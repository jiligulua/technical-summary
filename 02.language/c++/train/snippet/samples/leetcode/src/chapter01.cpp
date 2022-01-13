#include "base.h"
#include "chapter01.h"

namespace npt
{

    struct Person
    {
        int age_;
        void showAge(int base)
        {
            cout << base + age_ << '\n';
        }
    };

    void algorithm_interview_summarize()
    {
        vector<int> nums1{1, 3, 4, 4, 3, 1, 5};
        int ret = singleNumber(nums1);
        cout << "singleNumber: " << ret << '\n';

        Person p1{7};
        Person p2{39};
        Person p3{34};
        Person p4{3};
        vector<Person> persons{p1, p2, p3, p4};
        for_each(begin(persons), end(persons), bind(mem_fn(&Person::showAge), placeholders::_1, 10));
        // auto showAgeFn = mem_fn(&Person::showAge);
        // for_each(begin(persons), end(persons), showAgeFn);
        // showAgeFn(p1);

        vector<int> arr{5, 6, 1, 2, 4, 7, 9, 10, 8};
        quick_sort(arr, 0, arr.size());

        vector<int> arr2{1, 6, 1, 1, 4, 1, 1, 10, 8};
        ret = majorityElement(arr2);

        vector<vector<int>> nums3 {{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}};
        searchMatrix(nums3, 5);

        vector<int> nums41 {4,5,6,0,0,0};
        vector<int> nums42 {1,2,3};
        merge(nums41, 3, nums42, 3);
    }

    int singleNumber(vector<int> &nums)
    {
        if (nums.empty())
            return 0;

        int n = 0;
        for (auto item : nums)
            n ^= item;

        return n;

        // return std::accumulate(cbegin(nums), cend(nums), 0, bit_xor<int>());
    }

    // 摩尔投票法
    // 摩尔投票算法是基于这个事实
    // 每次从序列里选择两个不相同的数字删除掉（或称为“抵消”），
    // 最后剩下一个数字或几个相同的数字，
    // 就是出现次数大于总数一半的那个
    int majorityElement(vector<int> &nums)
    {
        int a = nums[0];
        int sum = 1;
        for (int i = 1; i < nums.size(); i++)
        {
            if (a == nums[i])
            {
                sum++;
            }
            else
            {
                sum--;
                if (sum == 0)
                {
                    a = nums[i + 1];
                }
            }
        }
        return a;
    }

    void quick_sort(vector<int> &arr, int begin, int end)
    {
        if (begin >= end)
            return;

        int pos = partition_hoare(arr, begin, end);
        quick_sort(arr, begin, pos);
        quick_sort(arr, pos + 1, end);
    }

    // Hoare-Partition 霍尔
    int partition_hoare(vector<int> &arr, int begin, int end)
    {
        int pivot = arr[begin];
        while (begin < end)
        {
            while (begin < end && arr[--end] >= pivot)
                ;
            arr[begin] = arr[end];
            while (begin < end && arr[++begin] <= pivot)
                ;
            arr[end] = arr[begin];
        }
        arr[begin] = pivot;
        return begin;
    }

    // Lomuto-Partition 洛穆托
    int partition_lomuto(vector<int> &arr, int begin, int end)
    {
        int pivot = arr[begin];
        // Last position where puts the no_larger element.
        int pos = begin;
        for (int i = begin + 1; i != end; i++)
        {
            if (arr[i] <= pivot)
            {
                pos++;
                if (i != pos)
                {
                    swap(arr[pos], arr[i]);
                }
            }
        }
        swap(arr[begin], arr[pos]);
        return pos;
    }

    bool searchMatrix(vector<vector<int>> &matrix, int target)
    { if (matrix.empty())
            return false;

        int pivot_row = matrix.size();
        int pivot_col = matrix[0].size();

        int cur_row = 0;
        int cur_col = pivot_col - 1;

        while(cur_row < pivot_row && 0 <= cur_col)
        {
            int temp = matrix[cur_row][cur_col];
            if (temp == target)
                return true;
            else if (target > temp)
                ++cur_row;
            else
                --cur_col;
        }

        return false;
    }

    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
    {
        if (n == 0)
            return;

        int index1 = m - 1;
        int index2 = n - 1;
        int pivot = m + n;

        while (index2 >= 0)
        {
            --pivot;
            if (index1 < 0)
            {
                nums1[pivot] = nums2[index2];
                --index2;
                continue;
            }
            
            if(nums2[index2] >= nums1[index1])
            {
                nums1[pivot] = nums2[index2];
                --index2;
            } 
            else
            {
                nums1[pivot] = nums1[index1];
                --index1;
            }
        }
    }

    int superEggDrop(int k, int n)
    {
        return 0;
    }
}