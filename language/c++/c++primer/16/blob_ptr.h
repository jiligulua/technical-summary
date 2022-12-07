#ifndef SEDNA_BLOB_PTR_H_
#define SEDNA_BLOB_PTR_H_

#include <vector>
#include <string>
#include <memory>
#include <cstddef>

namespace yh {

template <typename T>
class BlobPtr {
 public:
  BlobPtr() : curr(0) {}
  BlobPtr(Blob<T> &a, std::size_t sz = 0)
    : wptr(a.data)
	, curr(sz) {}

  T& operator*() const {
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
  }

  BlobPtr& operator++();
  BlobPtr& operator--();
  
  BlobPtr operator++(int);
  BlobPtr operator--(int);
  
 private:
  std::shared_ptr<std::vector<T>> check(std::size_t, const std::string &msg) const;
  
  std::weak_ptr<std::vector<T>> wptr;
  std::size_t curr;
};

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
  check(curr, "increment past end of BlobPtr");
  ++curr;
  return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
  --curr;
  check(curr, "decrement past begin of BlobPtr");
  return *this;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int) {
  BlobPtr ret = *this;
  ++*this;
  return ret;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator--(int) {
  BlobPtr ret = *this;
  --*this;
  return ret;
}


} // namespace yh

#endif // SEDNA_BLOB_PTR_H_
