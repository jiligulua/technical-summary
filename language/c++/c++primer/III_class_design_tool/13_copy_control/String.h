#ifndef MARS_STRING_H_
#define MARS_STRING_H_

#include <memory>
#include <utility>
#include <iostream>

class String {
  friend std::ostream& operator<<(std::ostream&, const String&);
 public:
  String() : String("") {}
  String(const char*);
  String(const String&);
  String& operator=(const String&);
  String(String&&) noexcept;
  String& operator=(String&&) noexcept;
  ~String();

  char& operator[](std::size_t n) { return elements_[n]; }
  const char& operator[](std::size_t n) const { return elements_[n]; }
  const char* C_Str() const { return elements_; }
  std::size_t Size() const { return end_ - elements_; } 
  std::size_t Length() const { return end_ - elements_; }

 private:
  void range_initializer(const char*, const char*);
  std::pair<char*, char*> alloc_n_copy(const char*, const char*);
  void free();

  char* elements_;
  char* end_;
  std::allocator<char> alloc_; // 只是一个内存分配工具，没有什么神秘的。
};

#endif // MARS_STRING_H_
