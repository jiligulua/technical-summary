#include <iostream>
#include <stack>

using std::stack;
using std::cout;
using std::endl;

bool isPopOrder(const int *pPush, const int *pPop, int len) {
  if (pPush == nullptr || pPop == nullptr || len <= 0)
    return false;

  std::size_t i = 0;
  std::size_t j = 0;
  stack<int> s;
  while (i != len) {
    s.push(*(pPush+i++));
	if (s.top() != *(pPop+j)) {
	  continue;
	} else {
	  ++j;
	  s.pop();
	}
  }

  while (!s.empty()) {
    if (s.top() == *(pPop+j)) {
	  ++j;
	  s.pop();
	} else {
	  break;
	} 
  }

  return s.empty();
}

int main() {
  const char *pStr = "I love c++, I love world!";
  int pPush[] {1, 2, 3, 4, 5};
  int pPop[] {4, 5, 3, 2, 1};
  int len = 5;
  cout << "is Pop order ? " << isPopOrder(pPush, pPop, len) << endl;
	
  int pPush2[] {1, 2, 3, 4, 5};
  int pPop2[] {4, 5, 3, 1, 2};
  int len2 = 5;
  cout << "is Pop order ? " << isPopOrder(pPush2, pPop2, len2) << endl;
  return 1;
}
