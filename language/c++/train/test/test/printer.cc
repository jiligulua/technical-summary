#include <algorithm>
#include <iostream>

namespace utils {

template <typename Container>
void Print(const Container& c) {
  std::for_each(c.cbegin(), c.cend(), [](const auto& item) {
    std::cout << item << " ";                  
  });
  std::cout << std::endl;
} 

} // namespace utils

#include <vector>
int main() {
  std::vector<int> ivec {1,2,3,4,5,6,7,4,32,2};
  utils::Print(ivec);
}
