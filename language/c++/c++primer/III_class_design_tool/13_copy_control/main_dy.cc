#include "str_vec.h"
#include <iostream>
#include <algorithm>

int main(int argc, char* argv[]) {
  using namespace std;

  StrVec strvec; 
  strvec.PushBack("Hello");
  strvec.PushBack("Baidu");
  strvec.PushBack("I love you");

  auto beg = strvec.Begin();
  while (beg != strvec.End())
    cout << *beg++ << " ";
  cout << endl; 
	
  return 0;
}


#ifndef MAR_COPY_CONTROL_STR_VEC_H_
#define MAR_COPY_CONTROL_STR_VEC_H_

#include <string>
#include <memory>

using std::string;

class StrVec {
 public:
  StrVec() : elements_(nullptr), first_free_(nullptr), cap_(nullptr) {}
  StrVec(const StrVec&);
  StrVec& operator=(const StrVec&);
  ~StrVec();
  void PushBack(const std::string&);
  std::size_t Size() const { return first_free_ - elements_; }
  std::size_t Capacity() const { return cap_ - elements_; }
  std::string* Begin() const { return elements_; }
  std::string* End() const { return first_free_; }

  void Reserve(std::size_t n);
  void Resize(std::size_t n);
  void Resize(std::size_t n, const std::string& s);

 private:
  void check_n_alloc() {
    if (Size() == Capacity())
	  reallocate();
  }

  std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
  void free();
  void reallocate(void);
  void reallocate(std::size_t new_capacity);

  static std::allocator<std::string> alloc_;

  std::string* elements_;
  std::string* first_free_;
  std::string* cap_;
};

#endif// MAR_COPY_CONTROL_STR_VEC_H_


#include "str_vec.h"
#include <utility>
#include <algorithm>
#include <string>

using std::string;

StrVec::StrVec(const StrVec& s) {
  auto data = alloc_n_copy(s.Begin(), s.End());
  elements_ = data.first;
  first_free_ = cap_ = data.second;
}

StrVec& StrVec::operator=(const StrVec& rhs) {
  auto data = alloc_n_copy(rhs.Begin(), rhs.End());
  free();
  elements_ = data.first;
  first_free_ = cap_ = data.second;
  return *this;
}

StrVec::~StrVec() {
  free();
}

std::pair<std::string*, std::string*> 
StrVec::alloc_n_copy(const string* b, const string* e) {
  auto data = alloc_.allocate(e - b);
  return {data, uninitialized_copy(b, e, data)};// 返回构造之后的Begin和End指针 
}

void StrVec::free() {
  if (elements_) {
    for (auto p = first_free_; p != elements_;) 
	  alloc_.destroy(--p);
	alloc_.deallocate(elements_, cap_ - elements_);
  }
}

void StrVec::PushBack(const std::string& rhs) {
  check_n_alloc();
  alloc_.construct(first_free_++, rhs);
}

void StrVec::Reserve(std::size_t n) {
  if (n > Capacity())
	reallocate(n);
}

void StrVec::reallocate(void) {
  auto new_capacity = Size() ? 2 * Size() : 1;
  reallocate(new_capacity);
}

void StrVec::reallocate(std::size_t new_capacity) {
  auto new_data = alloc_.allocate(new_capacity);
  auto dest = new_data;
  auto elem = elements_;
  for (std::size_t i = 0; i != Size(); ++i) 
	alloc_.construct(dest++, std::move(*elem++));

  free();
  elements_ = new_data;
  first_free_ = dest;
  cap_ = elements_ + new_capacity;
}

inline
void StrVec::Resize(std::size_t n) {
  Resize(n, "");
}

void StrVec::Resize(std::size_t n, const std::string& s) {
  if (n > Size()) {
    while (Size() < n)
	  PushBack(s);
  } else if (n < Size()) { // 目前的情况是期望值比Size小
    while (Size() > n) // 只要是一直是这样的情况
	  alloc_.destroy(--first_free_); // 销毁多余的对象
  }
}

std::allocator<std::string> StrVec::alloc_;
