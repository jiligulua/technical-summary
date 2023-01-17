#include <mercury/task_list.h>

#include <cstring>

#include <deque>
using std::deque;
#include <stdexcept>
#include <vector>
using std::vector;

namespace mercury {


// 57：和为s的数字
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

// 58: 反转字符串
// 提炼出两头指针的函数，是关键
void Reverse(char *start, char *end) {
	if (start == nullptr || end == nullptr)
		return; 

	while (start < end) {
		auto tmp = *start;
		*start = *end;
		*end = tmp;
		++start;
		--end;
	}
}

char* ReverseSequence(char *data) {
	if (data == nullptr)
		return nullptr;

	char *start = data;
	char *end = data + strlen(data) - 1;
	Reverse(start, end);
	
	start = end = data;
	while (*start != '\0') {
		if (*start == ' ') {
			++start;
			++end;
		} else if (*end == ' ' || *end == '\0') {
			Reverse(start, --end);
			start = ++end;
		} else {
			++end;
		}
	}

	return data;
}


char* LeftRotateStr(char *data, int n) {
	if (data == nullptr || n < 1) 
		return nullptr;

	int len = static_cast<int>(strlen(data));
	if (n >= len) 
		return data;

	Reverse(data, data+len-1);
	Reverse(data, data+len-n-1);
	Reverse(data+len-n, data+len-1);

	return data;
}

vector<int> GetMaxSequence(int *data, int m, int n) {
	if (data == nullptr || m < 1 || n < 1 || n < m)
		throw std::invalid_argument("invliad argument");

	if (m == 1)
		return vector<int>(data, data+n);

	std::deque<int> d;
	d.push_back(0);
	if (data[d.front()] > data[1])
		d.push_back(1);
	else
		d.push_front(1);

	for (int i = 2; i < m; ++i) {
		if (data[i] > data[d.front()]) {
			d.push_front(i);
			d.pop_back();
		}	else if (data[i] > data[d.back()]){
			d.pop_back();
			d.push_back(i);
		}
	}

	vector<int> ret;
	ret.push_back(data[d.front()]);

	for (int i = m; i < n; ++i) {
		if (d.front() == i-m) 
			d.pop_front();
		else if (d.back() == i-m)
			d.pop_back();
			
		if (d.size() == 1) {
			if (data[i] > data[d.front()]) 
				d.push_front(i);
			else
				d.push_back(i);
		} else {
			if (data[i] > data[d.front()]) {
				d.push_front(i);
				d.pop_back();
			} else if (data[i] > data[d.back()]) {
				d.pop_back();
				d.push_back(i);
			}
		}
		ret.push_back(data[d.front()]);
	}

	return ret;
}

vector<int> GetMaxSequence2(const vector<int>& num, unsigned int size) {
	vector<int> max;
	if (num.size() >= size && size >= 1) {
		deque<int> index;

		// 算法永远都可以改进，只要时间允许的话，以下的算法，保证有1或2个数据或多个数据
		for (unsigned i = 0; i < size; ++i) {
			while (!index.empty() && num[i] >= num[index.back()])
				index.pop_back();

			index.push_back(i);
		}

		for (unsigned i = size; i < num.size(); ++i) {
			max.push_back(num[index.front()]);

			while (!index.empty() && num[i] >= num[index.back()])
				index.pop_back();
			if (!index.empty() && index.front() <= (int)(i-size))
				index.pop_front();

			index.push_back(i);
		}

		max.push_back(num[index.front()]);
	}

	return max;
}



} // namespace mercury
