#ifndef MERCUY_TASK_LIST_H_
#define MERCUY_TASK_LIST_H_

#include <deque>
#include <stdexcept>
#include <tuple>
#include <vector>

using std::vector;

namespace mercury {

// 57：和为s的数字
std::tuple<bool, int, int> GetItemsFromSum(int sum, int *data, int len);
std::tuple<bool, vector<vector<int>>> GetSerial(int sum);

// 58:翻转
void Reverse(char *start, char *end); 
char* ReverseSequence(char *data); 
char* LeftRotateStr(char *data, int n); 

// 59：队列的最大值
vector<int> GetMaxSequence(int *data, int m, int n);
vector<int> GetMaxSequence2(const vector<int>& num, unsigned int size);

template <typename T>
class QueueWithMax {
 public:
	QueueWithMax() : cur_index_(0) {}
	
	void PushBack(T number) {
		while (!max_.empty() && number >= max_.back().number) 
			max_.pop_back();

		InternalData internalData = {number, cur_index_};
		max_.push_back(internalData);
		data_.push_back(internalData);

		++cur_index_;
	}

	void PopFront() {
		if (data_.empty())
			throw std::exception("queue is empty");

		if (max_.front().index == data_.front().index)
			max_.pop_front();

		data_.pop_front();
	}

	T max() const {
		if (max_.empty())
			throw std::exception("queue is empty");

		return max_.front().number;
	}

 private:
	struct InternalData {
		T number;
		unsigned index;
	};
	std::deque<InternalData> data_;
	std::deque<InternalData> max_;
	unsigned cur_index_;
};

} // namespace mercury

  
#endif // MERCUY_TASK_LIST_H_
