#include <iostream>

using std::cout;
using std::endl;
using std::cin;


bool IsSearchTree(int *pstr, unsigned len) {
  if (pstr == nullptr || len == 0) return false;
  if (len == 1) return true;

  unsigned cnt = len-1;
  unsigned index = 0;
  int root = *(pstr+len-1);
  while (*(pstr+index) < root && index != cnt)
    ++index;

  if (index == 0) {
    while (++index != cnt)
	  if (*(pstr+index) < root)
	    return false;
	if (index == cnt)
	  return IsSearchTree(pstr, cnt);
  } else if (index == cnt) {
	return IsSearchTree(pstr, cnt);
  } else {
	return IsSearchTree(pstr, index) && IsSearchTree(pstr+index, cnt-index);
  }

  return false; 
}

int main() {
  cout << "Input int array, or input q for end" << endl;
  int num;
  int len=0;
  int *pint = new int[128];
  while (cin >> num) {
    *(pint + len++) = num;
  }
  cout << endl;

  bool ret = IsSearchTree(pint, len);

  cout << (ret ? "It is a search tree" : "It is not a search tree") << endl;

  	
}
