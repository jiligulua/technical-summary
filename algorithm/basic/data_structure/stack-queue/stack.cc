#include <vector>
#include <array>
#include <iostream>
#include <cassert>

using std::vector;
using std::array;
using std::cout;
using std::endl;

template <typename T>
class Stack {
 private:
  vector<T> value_;
  T min_;
 public:
  const T& Min() const;
  void Pop();
  void Push(const T& data);
  const T Top();
  bool IsEmpty();
};

template <typename T> 
const T& Stack<T>::Min() const {
  assert(!value_.empty()); // 当为false时，弹框
  return min_;
}

template <typename T>
void Stack<T>::Push(const T& data) {
  if (value_.empty())
	min_ = data;

  auto diff = min_ - data;
  value_.push_back(diff);
  
  if (diff > 0)
	min_ = data;
}

template <typename T>
void Stack<T>::Pop() {
  assert(!value_.empty());
  if (value_.back() < 0) {
    value_.pop_back();
  } else {
    min_ += value_.back();
    value_.pop_back();
  }
}

template <typename T>
const T Stack<T>::Top() {
  assert(!value_.empty());
  if (value_.back() <= 0) {
    return min_ - value_.back();
  } else {
    return min_ + value_.back();
  }
}

template <typename T> 
bool Stack<T>::IsEmpty() {
  return value_.empty();
}

int main() {
  Stack<int> stack;
  array<int, 7> arr {6,8,15,2,3,1,2};
  for (auto i : arr) {
    stack.Push(i);
    cout << "Input: " << i << " 当前最小值为: ";
    cout << stack.Min() << endl;
  }

  cout << "出栈：" << endl;
  while (!stack.IsEmpty()) {
    cout << "output stack value: " << stack.Top() << " current min value: " << stack.Min() << endl;
	stack.Pop();
  }
}

