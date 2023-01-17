#include <iostream>
using std::cout; using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;

// 65.股票问题{9,5,3,4,5,16,43,23,8}
int MaxDiff(const std::vector<int> &data) {
  if (data.size() < 2)
    return 0;

  auto min = data.at(0);
  auto max_diff = data.at(1) - min;
  for (size_t i = 2; i < data.size(); ++i) {
    if (data.at(i-1) < min)
      min = data.at(i-1);

    auto cur_diff = data.at(i) - min;
    if (cur_diff > max_diff)
      max_diff = cur_diff;
  }
  return max_diff;
}

// 66.限制性计算 1+2+3+ ... + n
// solution 1
class Temp {
 public:
  Temp() { ++n_; sum_ += n_;}
  static unsigned sum() { return sum_; }
  static void reset() { n_= 0; sum_ = 0;}

 private:
  static unsigned n_;
  static unsigned sum_;
};

unsigned Temp::n_ = 0;
unsigned Temp::sum_ = 0;

// solution 2
class A;
A* array[2];

struct A {
  virtual unsigned sum(unsigned n) { return 0; }
};

struct B : A {
  virtual unsigned sum(unsigned n) { 
    return array[!!n]->sum(n-1) + n;
  }
};

// solution 3
typedef unsigned (*SumFun)(unsigned n);

unsigned SolutionTerminator(unsigned n) {
  return 0;
}

unsigned SolutionLoop(unsigned n) {
  static SumFun arr[2] = {SolutionTerminator, SolutionLoop};
  return n + arr[!!n](n-1);
}

// solution 4
template <unsigned n> 
struct Accumulate {
  enum Num { N = n + Accumulate<n-1>::N };
};

template <> 
struct Accumulate<1> {
  enum Num { N = 1 };
};

unsigned GetSum1(unsigned n) {
  Temp::reset();

  Temp* p = new Temp[n];
  delete[] p;

  return Temp::sum();
}

unsigned GetSum2(unsigned n) {
  A a;
  B b;
  array[0] = &a;
  array[1] = &b;
  return array[!!n]->sum(n);
}

unsigned GetSum3(unsigned n) {
  return SolutionLoop(n);
}

// 模板需要预编译处理，只能使用常量来明确初始化类模板而不能使用变量
// 所以，下列的定义是错误的
//unsigned GetSum4(unsigned n) {
//  return Accumulate<n>::N;
//}

int main() {
  cout << "Test 65---------------------------------" << endl;
  vector<int> ivec = {9,5,3,4,5,16,43,23,8};
  cout << "65 The max diff is " << MaxDiff(ivec) << endl;

  cout << "Test 66---------------------------------" << endl;
  cout << "The sum of 10 is " << GetSum1(10) << endl;
  cout << "The sum of 10 is " << GetSum2(10) << endl;
  cout << "The sum of 10 is " << GetSum3(10) << endl;
  cout << "The sum of 10 is " << Accumulate<10>::N << endl;
}
