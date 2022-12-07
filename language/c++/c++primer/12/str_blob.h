#ifndef SEDNA_STR_BLOB_H_
#define SEDNA_STR_BLOB_H_

#include <memory>
#include <stdexcept>
#include <vector>
#include <string>
#include <initializer_list>

using std::string;
using std::vector;

class StrBlob {
 public:
  using size_type = std::vector<string>::size_type;
  
  StrBlob();
  StrBlob(std::initializer_list<string> il);

  size_type Size() const { return data_->size(); }
  bool Empty() const { return data_->empty(); }

  void PushBack(const string &val) { data_->emplace_back(val); }
  void PopBack();

  string& Front();
  string& Back();

  const string& Front() const;
  const string& Back() const;

 private:
  void check(size_type i, const string &msg) const;
  std::shared_ptr<vector<string>> data_;
};

#endif 
