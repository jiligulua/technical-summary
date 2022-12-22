#ifndef MARS_STR_BLOB_PTR_H_
#define MARS_STR_BLOB_PTR_H_

#include <memory>
#include <vector>
#include <string>
#include "str_blob.h"

class StrBlobPtr {
 public:
  StrBlobPtr() : curr_(0) {}
  StrBlobPtr(StrBlob& a, std::size_t sz = 0)
      : wptr(a.data_)
	  , curr_(sz) {}

  std::string& deref() const;
  StrBolbPtr& incr(); // 前缀递增

 private:
  std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
  
  std::weak_ptr<std::vector<std::string>> wptr_;
  std::size_t curr_;
};

#endif// MARS_STR_BLOB_PTR_H_
