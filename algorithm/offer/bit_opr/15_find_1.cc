#include <iostream>

int FindNumberOf1(int n) {
  int count = 0;
  unsigned int flag = 1;
  
  while(flag) {
    if (n & flag) 
	  ++count;

	flag = flag << 1;
  }

  return count;
}

int FindNumberOf1Ex(int n) {
  int count = 0;
  
  while (n) {
    ++count;
	int m = n - 1;
	n = m & n;
  }
  
  return count;
}

int main() {
  int count = FindNumberOf1Ex(5);
  int count2 = FindNumberOf1(-5);

  return 1;

}
