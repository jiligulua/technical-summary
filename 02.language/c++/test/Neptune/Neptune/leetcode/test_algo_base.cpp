#include "test_algo_base.h"
#include <numeric>

namespace npt
{
	int singleNumber(vector<int> nums)
	{
		return std::accumulate(begin(nums), end(nums), 0, bit_xor<int>());
	}
}