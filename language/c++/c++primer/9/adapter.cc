#include <iostream>
#include <queue>
#include "common.h"

using std::queue;

int main() {
  queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  q.push(4);

  q.pop();
  
  std::cout << q.front() << std::endl;

}
