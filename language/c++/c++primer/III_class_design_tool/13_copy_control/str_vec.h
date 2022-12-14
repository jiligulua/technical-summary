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
