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

    void test_chapter01()
    {
        vector<int> nums{1, 3, 4, 4, 3, 1, 5};
        int ret = singleNumber(nums);
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

        vector<int> arr {5, 6, 1, 2, 4, 7, 9, 10, 8};
        quick_sort(arr, 0, arr.size());

        vector<int> arr2 {1, 6, 1, 1, 4, 1, 1, 10, 8};
        ret = majorityElement2(arr2);
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

    int majorityElement(vector<int> &nums)
    {
        
        return 0;
    } 
    
    
    // 摩尔投票法
    // 摩尔投票算法是基于这个事实
    // 每次从序列里选择两个不相同的数字删除掉（或称为“抵消”），
    // 最后剩下一个数字或几个相同的数字，
    // 就是出现次数大于总数一半的那个
    int majorityElement2(vector<int> &nums)
    {
		  int a=nums[0];
		  int sum=1;
          for (int i = 1; i < nums.size(); i++) {
			  if(a==nums[i]) {
				  sum++;
			  }else {
				  sum--;
				  if(sum==0) {
					  a=nums[i+1];
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
        quick_sort(arr, pos+1, end);
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


   

}