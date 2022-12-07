#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include "common.h"

using namespace std;

int main() {
  vector<int> ivec {1,2,2,3,8,5,4,32,21,31,25};
  std::cout << "lower bound of vector "
  multiset<int, greater<int>> iset(ivec.cbegin(), ivec.cend());
  std::cout << iset.size() << " " << iset.max_size() << std::endl;

  Print(iset);
}
