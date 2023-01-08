#include <mercury/task_list.h>

namespace mercury {


std::tuple<bool, int, int> GetItemsFromSum(int sum, int *data, int len) {
	if (data == nullptr || len < 2)
		return {false, -1, -1};

	int i = 0, j = len-1;
	int cur_sum = 0;
	while (i < j) {
		cur_sum = data[i] + data[j];
		if (cur_sum == sum)
			return {true, i, j};
		else if (cur_sum > sum)
			--j;
		else
			++i;
	}

	return {false, -1, -1};
}

std::tuple<bool, vector<vector<int>>> GetSerial(int sum) {
	if (sum < 2)
		return {false, {}};

	int i = 1, j = 2;
	int cur_sum = i+j;
	using vecs = vector<vector<int>>;
	std::tuple<bool, vecs> ret(false, {});
	while (i < (sum+1)/2 && j < sum) {
		if (cur_sum == sum) {

			std::get<0>(ret) = true;
			vector<int> item;
			for (int k = i; k <= j; ++k)
				item.push_back(k);
			std::get<1>(ret).push_back(item);
			
			++j;
			cur_sum +=j;
		} else if (cur_sum > sum) {
			cur_sum -= i;
			++i;
		} else {
			++j;
			cur_sum += j;
		}
	}

	return ret;
}

} // namespace mercury
