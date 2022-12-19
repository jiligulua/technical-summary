#include "String.h"
#include <algorithm>
#include <iostream>


String::String(const char* s) {
  char* sl = const_cast<char*>(s);
  while(*sl)
	++sl;
  range_initializer(s, sl);
  std::cout << "constructor" << std::endl;
}

String::String(const String& rhs) {
  range_initializer(rhs.elements_, rhs.end_);
  std::cout << "copy constructor" << std::endl;
}

void String::range_initializer(const char* first, const char* last) {
  auto new_str = alloc_n_copy(first, last);
  elements_ = new_str.first;
  end_ = new_str.second;
}

std::pair<char*, char*>
String::alloc_n_copy(const char* b, const char* e) {
  auto str = alloc_.allocate(e - b);
  return {str, std::uninitialized_copy(b, e, str)};
}

String& String::operator=(const String& rhs) {
  auto new_str = alloc_n_copy(rhs.elements_, rhs.end_);
  free();
  elements_ = new_str.first;
  end_ = new_str.second;
  std::cout << "copy-assignment" << std::endl;
  return *this;
}

String::String(String&& rhs) noexcept
    : elements_(rhs.elements_)
	, end_(rhs.end_) {
  rhs.elements_ = rhs.end_ = nullptr;	
  std::cout << "move construct" << std::endl;
}

String& String::operator=(String&& rhs) noexcept {
  if (this != &rhs) {
    free();
	elements_ = rhs.elements_; // manage old memory
	end_ = rhs.end_; // manage old memory
	rhs.elements_ = rhs.end_ = nullptr;
  }
  std::cout << "move-assignment" << std::endl;
  return *this;
}

String::~String() {
  free();
  std::cout << "destructor" << std::endl;
}

void String::free() {
  if (elements_) {
    std::for_each(elements_, end_, [this](char& c){ alloc_.destroy(&c); });
	alloc_.deallocate(elements_, end_-elements_);
  }
}

std::ostream& operator<<(std::ostream& os, const String& s) {
  os << s.C_Str();
  return os;
}
