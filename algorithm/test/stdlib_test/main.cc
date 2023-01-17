#include <algorithm>
#include <iterator>
#include <iostream>
using std::cout; using std::endl;
#include <set>
using std::set;
#include <string>
using std::string;
#include <vector>
using std::vector;

template <typename T>
void print(const T &t) {
  for (const auto &item : t) {
    cout << item << " ";
  }
  cout << endl;
}

int main() {
  set<string> strv1 = {"Hello", "World", "I", "really", "love", "you", "chris"};
  set<string> strv2 = {"I", "really", "love", "you", "so", "much", "do", "you", "remember", "Neo"};
  set<string> dst;

  std::set_union(strv1.begin(), strv1.end(), strv2.begin(), strv2.end(), std::inserter(dst, dst.begin()));
  print(dst);

  set<string> dst2;
  std::set_intersection(strv1.begin(), strv1.end(), strv2.begin(), strv2.end(), std::inserter(dst2, dst2.begin()));
  print(dst2);
  
  set<string> dst3;
  std::set_difference(strv1.begin(), strv1.end(), strv2.begin(), strv2.end(), std::inserter(dst3, dst3.begin()));
  print(dst3);

  set<string> dst4;
  std::set_symmetric_difference(strv1.begin(), strv1.end(), strv2.begin(), strv2.end(), std::inserter(dst4, dst4.begin()));
  print(dst4);
}
