#include <iostream>
#include <unistd.h>

int add(int a, int b) {
  return a+b;
}

void subCalc() {
 int j = 0;
 while (++j < 100000000) {}
 add(j, j);
}

void calc() {
  int i = 0;
  while(++i < 1000000000) {}

  subCalc();
  subCalc();
}

int main() {
  calc();
  calc();
  add(1, 2);
}
