#include <mercury/merge_sort.h>

#include <algorithm>
#include <vector>

namespace mercury {


void MergeSort::Sort(std::vector<int>& data) {
  if (data.size() <= 1)
	return;

  sort_core(data, 0, data.size()-1);
}

// 一个出口条件，
void MergeSort::sort_core(std::vector<int>& data, 
						  std::size_t start, 
						  std::size_t end) {
  if (start == end) {
	return;
  } else {
    int middle = ((end-start) >> 1 ) + start;
	sort_core(data, start, middle);  // 这样写比较复合逻辑思维，每次的递归就是为了划清界线
	sort_core(data, middle+1, end);  // 而整合的操作就是在merge中处理。
	merge(data, start, middle, end); // 只需要考虑两种情况：return的情况和过程中的任意一种
  }
}

void MergeSort::merge(std::vector<int>& src,
			          std::size_t start,
			          std::size_t middle,
			          std::size_t end) {
  std::vector<int> tmp(src.size());
  std::size_t k = start;
  std::size_t i = start, j = middle+1;

  while (i <= middle && j <= end) {
    if (src.at(i) < src.at(j)) 
	  tmp.at(k++) = src.at(i++);
	else 
	  tmp.at(k++) = src.at(j++);
  }

  while (i <= middle) 
    tmp.at(k++) = src.at(i++);

  while (j <= end) 
	tmp.at(k++) = src.at(j++);

  for (int i = start; i <= end; ++i)
	src.at(i) = tmp.at(i);
  //std::copy(tmp.begin(), tmp.end(), src.begin()+start);
}

int MergeSort::InverseCount(const std::vector<int> &data) {
	std::vector<int> src(data);

	if (data.size() < 2)
		return 0;

	return inverse_count_core(src, 0, src.size()-1);
}

int MergeSort::inverse_count_core(std::vector<int> &data, 
											int start,
											int end) {
	if (start == end)
		return 0;
	else {
		int middle = ((end-start) >> 1) + start;
		int left = inverse_count_core(data, start, middle);	
		int right = inverse_count_core(data, middle+1, end);
		return left + right + merge_inverse(data, start, middle, end); 	
	}
}

int MergeSort::merge_inverse(std::vector<int> &data, 
									int start,
									int middle,
									int end) {
	int i = middle;
	int j = end;
	int k = end;
	int count = 0;

	std::vector<int> tmp(data.size());
	while (i >= start && j > middle) {
		if (data.at(i) > data.at(j)) {
			tmp.at(k--) = data.at(i--);
			count += j - middle;
		} else {
			tmp.at(k--) = data.at(j--);
		}
	}

	while (i >= start)
		tmp.at(k--) = data.at(i--);
	
	while (j > middle)
		tmp.at(k--) = data.at(j--);

	std::copy(tmp.cbegin()+start, tmp.cbegin()+end+1, data.begin()+start);

	return count;
}

} // namespace mercury
