#include <iostream>
using std::cout; using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <tbb/parallel_for.h>
#include <boost/container_hash/hash.hpp>

#include <mercury/merge_sort.h>
#include <asteroid/simple_print.h>

int main(int argc, char* argv[]) {
  // test merge-sort
  vector<int> ivec {75, 34, 24, 43, 91, 63, 36, 12, 3, 52};
  mercury::MergeSort merge_sort;
//  vector<int>&& merge_data = merge_sort.Sort(ivec);
//  asteroid::print(merge_data);
  
  tbb::parallel_for(0, 10, [](int i) { std::cout << i << " ";});
  std::cout << std::endl;

  asteroid::print();

  boost::hash<std::string> string_hash;
  std::size_t h = string_hash("Hash me");

  std::cout << "Hash me: " << h << std::endl;

  std::cout << "We see again." << std::endl;
}
