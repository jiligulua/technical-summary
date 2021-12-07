#include "base.h"
#include "chapter01.h"

namespace npt
{
    void test_chapter01() 
    {
        vector<int> nums {1,3,4,4,3,1,5};
        int ret = singleNumber(nums);
        cout << "singleNumber: " << ret;
    }

	int singleNumber(vector<int> nums)
	{
        if (nums.empty())
            return 0;

        int n = 0;
        for (auto item : nums)
            n ^= item;
            
        return n;

		// return std::accumulate(cbegin(nums), cend(nums), 0, bit_xor<int>());
	}
}