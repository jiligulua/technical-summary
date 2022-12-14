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
