#include "str_vec.h"
#include <utility>
#include <algorithm>
#include <string>
#include <iterator>

using std::string;

StrVec::StrVec(const StrVec& s) {
  auto data = alloc_n_copy(s.Begin(), s.End());
  elements_ = data.first;
  first_free_ = cap_ = data.second;
}

StrVec::StrVec(std::initializer_list<string> il) {
  auto new_data = alloc_n_copy(il.begin(), il.end());
  elements_ = new_data.first;
  first_free_ = cap_ = new_data.second;
}

StrVec& StrVec::operator=(const StrVec& rhs) {
  auto data = alloc_n_copy(rhs.Begin(), rhs.End());
  free();
  elements_ = data.first;
  first_free_ = cap_ = data.second;
  return *this;
}

StrVec::StrVec(StrVec&& s) noexcept
    : elements_(s.elements_)
    , first_free_(s.first_free_)
    , cap_(s.cap_){
  s.elements_ = s.first_free_ = s.cap_ = nullptr;
}

StrVec& StrVec::operator=(StrVec&& rhs) noexcept {
  if (this != &rhs) {
    free();
	elements_ = rhs.elements_;
	first_free_ = rhs.first_free_;
	cap_ = rhs.cap_;
	rhs.elements_ = rhs.first_free_ = rhs.cap_ = nullptr; // 移动源处于可析构状态
  }
  return *this;
}

StrVec& StrVec::operatori=(std::initializer_list<std::string> il) {
  auto data = check_n_alloc(il.begin(), il.end();
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
	std::for_each(elements_, first_free_, 
				  [](std::string& s) { alloc_.destroy(&s); }); // for_each和lambda版本， 只需要指出范围以及对范围中元素执行什么操作即可，而for版本则需程序员小心控制指针的增减
    //for (auto p = first_free_; p != elements_;) 
	//  alloc_.destroy(--p);
	alloc_.deallocate(elements_, cap_ - elements_);
  }
}

void StrVec::PushBack(const std::string& rhs) {
  check_n_alloc();
  alloc_.construct(first_free_++, rhs);
}

void StrVec::PushBack(std::string&& rhs) {
  check_n_alloc();
  alloc_.construct(first_free_++, std::move(rhs));
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
 // auto new_data = alloc_.allocate(new_capacity);
 // auto dest = new_data;
 // auto elem = elements_;
 // for (std::size_t i = 0; i != Size(); ++i) 
 //   alloc_.construct(dest++, std::move(*elem++));

  auto first = alloc_.allocate(new_capacity);
  auto last = uninitialized_copy(std::make_move_iterator(Begin()),
				                 std::make_move_iterator(End()),
								 first); // 也就是说uninitialized_系列内部使用了construct函数

  free();
  elements_ = first;
  first_free_ = last;
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
