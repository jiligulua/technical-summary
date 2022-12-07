#include <iostream>
#include <iterator>
#include <queue>
#include <list>
#include <algorithm>
#include <vector>
#include <array>

using std::cout;
using std::endl;
using std::queue;
using std::list;
using std::priority_queue;
using std::vector;
using std::make_heap;

template<typename T>
void PrintContain(const T &t) {
  for (auto item : t)
    cout << item << " ";
  cout << endl;
}

struct node {
  friend bool operator<(const node &n1, const node &n2) {
    return n1.priority < n2.priority;
  }

  // 使用以下函数，存在错误，只能使用上面的重载函数，并且声明为friend才可以。
  //bool operator<(node rhs) {
  //  return priority < rhs.priority;
  //}
  unsigned priority;
  unsigned value;
};

int main() {
  //queue<int> q;// = {1, 2, 43, 24, 56};
  //priority_queue<int, vector<int>, std::greater<int>> q;// = {1, 2, 43, 24, 56};
  vector<int> vi = {1, 2, 43, 24, 56};
  //priority_queue<int> q(std::less<int>(), vi);// = {1, 2, 43, 24, 56};
  //q.push(1);
  //q.push(2);
  //q.push(42);
  //q.push(24);
  //q.push(56);
  //
  priority_queue<int> q(vi.begin(), vi.end());
  q.push(1);
  q.push(2);
  q.push(42);
  q.push(24);
  q.push(56);
  
  cout << "使用vector初始化priority_queue\n";
  while (!q.empty()) {
    cout << q.top() << " ";
	q.pop();
  }

  cout << endl;

  priority_queue<node> qn;
  node b[5];
  b[0].priority = 9; b[0].value = 1;
  b[1].priority = 6; b[1].value = 4;
  b[2].priority = 4; b[2].value = 6;
  b[3].priority = 3; b[3].value = 7;
  b[4].priority = 1; b[4].value = 9;

  qn.push(b[0]);
  qn.push(b[1]);
  qn.push(b[2]);
  qn.push(b[3]);
  qn.push(b[4]);


  cout << "自定义类，并重载operator<比较node类，可指定优先级和对应的处理数据" << endl;
  while (!qn.empty()) {
    cout << qn.top().priority << " " << qn.top().value << endl;
	qn.pop();
  }

  cout << endl;


  cout << "测试push_heap，将vector的数据存入push_heap中" << endl;
  vector<int> vi2 = {38, 29, 32, 17, 26, 15, 11, 9, 10, 60};
  PrintContain(vi2);
  
  std::push_heap(vi2.begin(), vi2.end());
  PrintContain(vi2);

  cout << "测试make_heap\n";
  vector<int> vi3 = {12, 1, 38, 29, 32, 17, 26, 15, 11, 9, 10, 60};
  make_heap(vi3.begin(), vi3.end());
  PrintContain(vi3);

  cout << "vi3 is heap? " << (is_heap(vi3.begin(), vi3.end(), std::greater<int>()) ? "Yes" : "No") << endl;
  cout << "pop_heap\n";
  pop_heap(vi3.begin(), vi3.end()-1);
  PrintContain(vi3);
  
  cout << "vi3 is heap? " << (is_heap(vi3.begin(), vi3.end()) ? "Yes" : "No") << endl;

  cout << "Using array to test make_heap" << endl;
  std::array<int, 6> ai = {23, 21, 4, 10, 90, 100};
  PrintContain(ai);

  cout << "make_heap\n";
  make_heap(ai.begin(), ai.end());
  PrintContain(ai);

  cout << "sort_heap\n";
  std::sort_heap(ai.begin(), ai.end());
  PrintContain(ai);
  return 1;
}
