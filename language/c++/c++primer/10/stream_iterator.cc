#include <iterator>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "SalesItem.h"

void TestStreamIterator() {
  std::cout << __func__ << std::endl;
  std::istream_iterator<SalesItem> is_iter(std::cin), eof;
  std::ostream_iterator<SalesItem> os_iter(std::cout, " -------- ");
  SalesItem sum = *is_iter++;
  while (is_iter != eof) {
    if (is_iter->isbn() == sum.isbn()) {
	  sum += *is_iter++;
	} else {
	  os_iter = sum;
	  sum = *is_iter++;
	}
  }
  os_iter = sum;
}

void TestStreamIteratorSplit() {
  std::cout << __func__ << std::endl;
  std::istream_iterator<int> in_iter(std::cin), eof;
  std::ostream_iterator<int> os_iter(std::cout, " +++ ");
  while (in_iter != eof)
    os_iter = *in_iter++;
  std::cout << std::endl;
}

void ReadFileWithStreamIterator() {
   std::cout << __func__ << std::endl;
   std::ifstream in("readme.txt");
   std::istream_iterator<std::string> in_iter(in), eof;
   std::vector<std::string> svec;
   std::copy(in_iter, eof, std::back_inserter(svec));

   std::ostream_iterator<std::string> out_iter(std::cout, "++++\n");
   std::copy(svec.cbegin(), svec.cend(), out_iter);
}

void Eat1030() {
  std::cout << __func__ << std::endl;
  std::istream_iterator<int> in_iter(std::cin), eof;
  //std::vector<int> ivec(in_iter, eof);
  std::vector<int> ivec;
  std::copy(in_iter, eof, std::back_inserter(ivec));
  std::sort(ivec.begin(), ivec.end());
  std::ostream_iterator<int> out_iter(std::cout, " ");
  std::copy(ivec.cbegin(), ivec.cend(), out_iter);
}

void Eat1031() {
  std::cout << __func__ << std::endl;
  std::istream_iterator<int> in_iter(std::cin), eof;
  std::vector<int> ivec(in_iter, eof);
  std::sort(ivec.begin(), ivec.end());
  std::vector<int> ivec2;
  std::unique_copy(ivec.cbegin(), ivec.cend(), std::back_inserter(ivec2));

  std::ostream_iterator<int> out_iter(std::cout, " ");
  std::copy(ivec2.cbegin(), ivec2.cend(), out_iter);
}

void Eat1033() {
  std::ifstream in("number.txt");
  std::ofstream out_odd("odd.txt");
  std::ofstream out_even("even.txt");

  auto SpliteOddEven = [] (std::ifstream& in, std::ofstream& out_odd, std::ofstream& out_even){ 
    std::istream_iterator<int> in_iter(in), eof;
	std::ostream_iterator<int> out_odd_iter(out_odd, " ");
	std::ostream_iterator<int> out_even_iter(out_even, "\n");
	while (in_iter != eof) {
	  if (*in_iter % 2 == 0)
        out_even_iter = *in_iter;
	  else
		out_odd_iter = *in_iter;

	  ++in_iter;
	}
  };

  SpliteOddEven(in, out_odd, out_even);
}

int main() {
  //Eat1030();
  //Eat1031();
  Eat1033();
  //ReadFileWithStreamIterator();
  //TestStreamIteratorSplit();
  //TestStreamIterator();
}

