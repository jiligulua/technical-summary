#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

// 基本概念：前缀和后缀相同，独立分析子串，KmpSimpleSearch时间复杂度有O(n*m), 而KmpSearch变为O(n+m),使用STL中的vector<int>来替代，同时考虑使用指定长度的vector，提高效率，防止了重复创建复制和销毁的时间开销。

// 以下共涉及到3个模式匹配算法
// 1. 朴素模式匹配
// 2. KMP模式匹配
// 3. KMP改进版模式匹配
int KmpSimpleSearch(const string&s, const string& t) {
  int pos = -1;
  int i = 0;
  int j = 0;
  while (i < (s.size() - t.size()) && 
		 j < t.size()) {
    if (s.at(i) == t.at(j)) {
	  ++i;
	  ++j;
	} else {
	  j = 0;
	  i = i - j + 1;
	}
  }

  if (j == t.size())
	return i - j;
  else 
	return -1;
}

vector<int> BuildNext(const string& t) {
  vector<int> next(t.size(), -1);
  next.at(0) = 0;

  int index = 1;
  int j = 1;
  int pre_len = 0;
  while (j < t.size()) {
    if (t[pre_len] == t[j]) {
	  ++pre_len;
	  next.at(index++) = pre_len;
	  ++j;
	} else {
	  if (0 == pre_len) {
	    next.at(index++) = 0;
		++j;
	  } else {
	    pre_len = next.at(pre_len-1);
	  }
	}
  }

  return next;
}

int KmpSearch(const string& s, const string& t) {
  if (s.empty() || t.empty())
	return -1;

  vector<int> next = BuildNext(t);

  int i = 0;
  int j = 0;

  while (i < s.size() && j < t.size()) {
    if (s.at(i) == t.at(j)) {
	  ++i;
	  ++j;
	} else {
	  if (j > 0)		
	    j = next.at(j-1);
	  else
		++i;
	}
  }

  if (j == t.size())
	return i-j;
  else
    return 0;
}

int main() {
  //string s("abcababcabcabxxy");
  //string t("abcabx");

  string s("HelloWorldIfindyou");
  string t("dIf");
  //int pos = KmpSearch(s, t);
  int pos = KmpSimpleSearch(s, t);

  cout << "子串在主串中的椅子的编号是" << pos << endl;
}
