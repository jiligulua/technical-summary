#ifndef MARS_FOO_H
#define MARS_FOO_H

#include <vector>

class Foo {
 public:
   Foo sorted() &&;
   Foo sorted() const &;
 private:
  std::vector<int> data_;
};

#endif// MARS_FOO_H
