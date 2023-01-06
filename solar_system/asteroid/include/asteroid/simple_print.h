#ifndef ASTEROID_SIMPLE_PRINT_H_
#define ASTEROID_SIMPLE_PRINT_H_

#include <algorithm>
#include <iostream>
#include <vector>

namespace asteroid {

template <typename Container>
void print(const Container& c) {
  std::for_each(c.cbegin(), c.cend(), 
				[](const auto& item) {
				  std::cout << item << " "; 
				});
  std::cout << std::endl;
}

void print();

}

#endif // ASTEROID_SIMPLE_PRINT_H_
