#include "str_blob.h"

namespace yh {

StrBob::StrBob() 
    : data(std::make_shared<vector<string>>()) {}

StrBob::StrBob(std::initializer_list<string> il) 
    : data(std::make_shared<vector<string>>(il)) {}

void StrBob::check(size_type i, const string &msg) const
{
  if (i >= data->size())
    throw std::out_of_range(msg);
}

void StrBob::pop_back()
{
  check(0, "pop_back on empty StrBlob");
  data->pop_back();
}

string& StrBob::front()
{
  // 如果vector为空，check会抛出一个异常
  check(0, "front on empty StrBlob");
  return data->front();
}

string& StrBob::back()
{
  check(0, "back on empty StrBlob");
  return data->back();
}


} // namespace yh
