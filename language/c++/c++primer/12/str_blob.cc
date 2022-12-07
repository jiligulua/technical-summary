#include "str_blob.h"

StrBlob::StrBlob() 
    : data_(std::make_shared<vector<string>>()) { }

StrBlob::StrBlob(std::initializer_list<string> il)
	: data_(std::make_shared<vector<string>>(il)) { }

void StrBlob::check(size_type i, const string &msg) const {
  if (i >= data_->size())
    throw std::out_of_range(msg);
}

void StrBlob::PopBack() {
  check(0, "PopBack on empty StrBlob");
  data_->pop_back();
}

string& StrBlob::Front() {
  check(0, "Front o empty StrBlob");
  return data_->front();
}

string& StrBlob::Back() {
  return const_cast<string&>(static_cast<const StrBlob&>(*this).Back());
}

const string& StrBlob::Front() const {
  check(0, "Front on empty StrBlob");
  return data_->front();
}

const string& StrBlob::Back() const {
  check(0, "Back on empty StrBlob");
  return data_->back();
}
