#include <mercury/merge_sort.h>

#include <vector>

namespace mercury {

std::vector<int> MergeSort::Sort(const std::vector<int>& src) {
  if (src.size() <= 1)
	return src;

  std::vector<int> tmp(src);
  sort_core(src, tmp, 0, src.size()-1);
  return src;
}

void MergeSort::sort_core(const std::vector<int>& src, 
						  std::vector<int>& tmp, 
						  std::size_t start, 
						  std::size_t end) {
  if (start == end) {
    tmp.at(start) = src.at(end);
	return; 
  } else {
    int middle = ((end-start) >> 1 ) + start;
	sort_core(src, tmp, start, middle);
	sort_core(src, tmp, middle, end);
	merge(src, tmp, start, middle, end);
  }
}

void MergeSort::merge(const std::vector<int>& src,
			 std::vector<int>& tmp,
			 std::size_t start,
			 std::size_t middle,
			 std::size_t end) {
  std::size_t k = start;
  std::size_t i = start, j = middle+1;
  while (i != middle+1 && 
		 j != end+1) {
    if (src.at(i) < src.at(j)) {
	  tmp.at(k++) = src.at(i++);
	} else {
	  tmp.at(k++) = src.at(j++);
	}
  }

  if (i == middle+1) {
    while (j != end+1) 
	  tmp.at(k++) = src.at(j++);
  } else {
	while (i != middle+1) 
	  tmp.at(k++) = src.at(i++);
  }
}

} // namespace mercury
