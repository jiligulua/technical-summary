// Author: Chris
// This is a class of StrBob
#ifndef STR_BOB_H_
#define STR_BOB_H_

#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;

namespace yh {

class StrBob
{
 public:
  typedef vector<string>::size_type size_type;
	
  StrBob();
  StrBob(std::initializer_list<string> il);
	
  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }
	
  void push_back(const string &t) { data->push_back(t); }
  void pop_back();

  string& front();
  string& back();

 private:
  std::shared_ptr<vector<string>> data; 
  void check(size_type i, const string &msg) const;
};

} // namespace yh

#endif // STR_BOB_H_
