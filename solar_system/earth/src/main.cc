#include <iostream>
using std::cout; using std::endl;

#include <fstream>
#include <string>
using std::string;
#include <tuple>
#include <vector>
using std::vector;

#include <tbb/parallel_for.h>
#include <boost/container_hash/hash.hpp>

#include <asteroid/simple_print.h>
#include <mercury/merge_sort.h>
#include <mercury/task_list.h>

#include <earth/test_text_query.h>

int main(int argc, char* argv[]) {
  // test merge-sort
  //vector<int> ivec {75, 34, 24, 43, 91, 63, 36, 12, 3, 52};
  //vector<int> ivec {5, 4, 3, 2, 1};
  //asteroid::print(ivec);
  mercury::MergeSort merge_sort;
  //merge_sort.Sort(ivec);
	
	vector<int> ivec {7, 5, 6, 4};
	int inverse_count = merge_sort.InverseCount(ivec);
	std::cout << "Inverse count is " << inverse_count << std::endl;

  asteroid::print(ivec);
  
  tbb::parallel_for(0, 10, [](int i) { std::cout << i << " ";});
  std::cout << std::endl;

  asteroid::print();

  boost::hash<std::string> string_hash;
  std::size_t h = string_hash("Hash me");
  std::cout << "Hash me: " << h << std::endl;
  std::cout << "We see again." << std::endl;

	int data[] = {1, 2, 4, 7, 11, 15};
	auto ret = mercury::GetItemsFromSum(15, data, 6);
	if (std::get<0>(ret)) 
		cout << "tow number is " << data[std::get<1>(ret)] << " and " << data[std::get<2>(ret)] << std::endl;

	auto ret2 = mercury::GetSerial(15);
	if (std::get<0>(ret2)) {
		std::cout << "has serials" << std::endl;
		auto items = std::get<1>(ret2);
		for (const auto &vec : items) {
			std::for_each(vec.cbegin(), vec.cend(), [](int i) { std::cout << i << " "; });
			std::cout << std::endl;
		}
	}
	

	char src[] = "Hello World! I love you!";
	std::cout << "raw: " << src << std::endl;
	mercury::ReverseSequence(src);

	std::cout << "chg: " << src << std::endl;

	char src2[] = "abcdefg";
	int index = 6;
	std::cout << "raw: " << src2 << " index: " << index << std::endl;
	mercury::LeftRotateStr(src2, index);
	std::cout << "chg: " << src2 << std::endl;
	
	std::cout << "get max sequence " << std::endl;
	//int src3[] = {4, 5, 1, 2, 6, 2, 5, 1};
	//auto ret3 = mercury::GetMaxSequence(src3, 3, 8);
	//asteroid::print(ret3);

	std::vector<int> ivec4 {4,3,1,2,6,2,5,1};
	auto ret4 = mercury::GetMaxSequence2(ivec4, 3);
	asteroid::print(ret4);

	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "Test text query function:" << std::endl;
  std::ifstream is("/home/chris/technical-summary/solar_system/1.txt", std::ios::in);
  earth::RunQueries(is);

  std::vector<std::string> str;

}
