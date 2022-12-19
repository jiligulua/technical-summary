#include "foo.h"
#include <algorithm>
#include <iostream>

Foo Foo::sorted() && {
  std::cout << "右值引用" << std::endl;
  std::sort(data_.begin(), data_.end());
  return *this;  
}

Foo Foo::sorted() const & {
  std::cout << "左值引用" << std::endl;
  return Foo(*this).sorted();
}

