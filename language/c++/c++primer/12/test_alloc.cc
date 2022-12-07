#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
  std::allocator<string> alloc;

  constexpr unsigned size = 10;
  auto const p = alloc.allocate(size);
  auto q = p;
  string str;
  while (std::cin >> str && q - p < size && str != "#") {
    alloc.construct(q++, str);
  }

  unsigned length = q - p;
  q = p;
  while (q != p + length)
    cout << *q++ << " ";
  cout << endl;

  while (q != p + length)
    alloc.destroy(q++);

  alloc.deallocate(p, size);

  return 0;
}
