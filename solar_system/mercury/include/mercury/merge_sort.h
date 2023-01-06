#ifndef SOLAR_SYSTEM_MERCURY_MERGE_SORT_H_
#define SOLAR_SYSTEM_MERCURY_MERGE_SORT_H_

#include <vector>

namespace mercury {

class MergeSort {
 public:
  std::vector<int> Sort(const std::vector<int>& src);  

 private:
  void sort_core(const std::vector<int>& src, 
				 std::vector<int>& tmp, 
				 std::size_t start, 
				 std::size_t end);

  void merge(const std::vector<int>& src,
			 std::vector<int>& tmp,
			 std::size_t start,
			 std::size_t middle,
			 std::size_t end);
};

} // namespace mercury

#endif // SOLAR_SYSTEM_MERCURY_MERGE_SORT_H_
