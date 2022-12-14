#include "has_ptr.h"
#include <iostream>

using std::cout;
using std::endl;

HasPtr::~HasPtr() {
  delete ps;
}

//HasPtr::~HasPtr() {
//  if (--*use == 0) {
//    delete ps;
//	delete use;
//  }
//}

HasPtr& HasPtr::operator=(HasPtr rhs) {
  swap(*this, rhs);
  return *this;
}

//HasPtr& HasPtr::operator=(const HasPtr & rhs) {
//  ++*rhs.use;
//  if (--*use == 0) {
//    delete ps;
//	delete use;
//  }
//
//  ps = rhs.ps;
//  i = rhs.i;
//  use = rhs.use;
//
//  return *this;
//}
//

HasPtr& HasPtr::operator=(const string & rhs) {
  *ps = rhs;
  return *this;
}

string& HasPtr::operator*() {
  return *ps;
}

bool HasPtr::operator<(const HasPtr& rhs) const {
  return *ps < *rhs.ps;
}

inline
void swap(HasPtr & lhs, HasPtr & rhs) {
  using std::swap;
  cout << "交换 "  << *lhs.ps << "和" << *rhs.ps << endl;
  swap(lhs.ps, rhs.ps);
  swap(lhs.i, rhs.i);
}
