#ifndef SOLAR_SYSTEM_MERCURY_MERGE_SORT_H_
#define SOLAR_SYSTEM_MERCURY_MERGE_SORT_H_

#include <vector>

namespace mercury {

class MergeSort {
 public:
  void Sort(std::vector<int>& src);  
  int InverseCount(const std::vector<int> &data);

 private:
  void sort_core(std::vector<int>& src, 
				 std::size_t start, 
				 std::size_t end);

  void merge(std::vector<int>& src,
			 std::size_t start,
			 std::size_t middle,
			 std::size_t end);

	int inverse_count_core(std::vector<int> &data, 
												int start,
												int end);

	int merge_inverse(std::vector<int> &data, 
										int start,
										int middle,
										int end);

  
};

} // namespace mercury

#endif // SOLAR_SYSTEM_MERCURY_MERGE_SORT_H_
