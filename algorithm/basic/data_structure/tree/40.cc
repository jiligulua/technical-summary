#include <set>
#include <iostream>
#include <vector>
#include <algorithm>

  
using miset = std::multiset<int, std::greater<int>>;

void ExtractLittleNumbers(const std::vector<int> &vi, miset &mis, int k) {
  if (k < 1 || vi.size() < k)
    return;
  
  for (const auto & item : vi) {
    if (mis.size() < k) 
	  mis.insert(item);
	else {
	  auto beg = mis.begin();
	  if (*beg > item) {
	    mis.erase(beg);
		mis.insert(item);
	  }
	}
  
  }
}

int main() {
  		
  std::vector<int> ivec = {4, 5, 1 ,6, 2, 7, 3, 8};
  int k = 5;
  miset mis;
  ExtractLittleNumbers(ivec, mis, k);

  for (const auto & item : mis) 
    std::cout << item << " ";
  std::cout << std::endl;  

  return 1;
}
