#include "str_vec.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include "String.h"
#include "foo.h"

int main(int argc, char* argv[]) {
  using namespace std;
//
//  StrVec strvec; 
//  strvec.PushBack("Hello");
//  strvec.PushBack("Baidu");
//  strvec.PushBack("I love you");
//
//  auto beg = strvec.Begin();
//  while (beg != strvec.End())
//    cout << *beg++ << " ";
//  cout << endl; 
//

  std::vector<String> svec;
  svec.push_back("Hello");
//  svec.push_back("Baidu");
//  svec.push_back("See");
//  svec.push_back("you");
//  svec.push_back("again");
//

  Foo f;
  f.sorted();

  String s("I love C++, to be a export.");
  std::cout << s << std::endl;

  return 0;
}
