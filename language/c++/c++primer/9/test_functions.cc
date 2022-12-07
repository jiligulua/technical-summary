#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <array>
#include <list>
#include <forward_list>

using std::vector;
using std::deque;
using std::string;
using std::array;
using std::list;
using std::forward_list;


template <typename T> 
void Print(const T &t) {
  for (auto i : t) 
    std::cout << i << " ";
  std::cout << std::endl;
}

template <typename Iter>
void Print(Iter beg, const Iter & end) {
  while (beg != end) 
    std::cout << *beg++ << " ";
  
  std::cout << std::endl;
}

template <typename Iter, typename T>
bool FindItem(Iter beg, Iter end, T t) {
  while (beg != end) {
    if (*beg == t)
	  return true;

	 ++beg;
  }
  return false;
}

template <typename Iter, typename T>
Iter FindItemIterator(Iter beg, Iter end, T t) {
  while (beg != end) {
    if (*beg == t)
	  return beg;

	 ++beg;
  }
  return end;
}

template <typename T, typename U>
void CompareDifContainer(const T & t, const U & u) {
  std::cout << "first: ";
  Print(t);
  std::cout << "second: ";
  Print(u);
  auto vi_cter = t.cbegin();
  auto li_cter = u.cbegin();
  while(vi_cter != t.cend() && li_cter != u.cend()) {
    if (*vi_cter++ != *li_cter++) 
	  break;
  }
  if (vi_cter != t.cend() && li_cter != u.cend()) {
    std::cout << "first < second ? " << (*vi_cter < *li_cter) << std::endl; 
  } else {
    if (vi_cter != t.cend() && li_cter == u.cend()) {
	  std::cout << "first > second" << std::endl;
	} else if (vi_cter == t.cend() && li_cter != u.cend())
	  std::cout << "first < second" << std::endl;
	else
	  std::cout << "first == second" << std::endl;
  }
}

void Exercise918() {
  string word;
  //deque<string> dstr;
  list<string> dstr;
  while(std::cin >> word) {
    dstr.push_front(word);
  }
  //Print(dstr);
  Print(dstr.begin(), dstr.end());
}

void DoubleSpecifiedNumber(vector<int> &vi, int num) {
  auto beg = vi.begin();
  auto mid = vi.begin() + vi.size()/2;
  while (beg != vi.begin() + vi.size()/2) {
    if (*beg == num) {
	  beg = vi.insert(beg, 2*num);
	  ++beg;
	}
	++beg;
  }
}

template <typename T>
void RemoveOddItem(T &t) {
  auto it = t.begin();
  while (it != t.end()) {
    if (*it % 2)
	  it = t.erase(it);
	else
	  ++it;
  }
}

template <typename T>
void RemoveEvenItem(T &t) {
  auto it = t.begin();
  while (it != t.end()) {
    if (*it % 2)
	  ++it;
	else
	  it = t.erase(it);
  }
}

void RemoveOddItemFromForwardList(forward_list<int> &ifl) {
  auto pre = ifl.before_begin();
  auto cur = ifl.begin();
  while (cur != ifl.end()) {
    if (*cur % 2) { 
	  cur = ifl.erase_after(pre);
	} else {
	  pre = cur;
	  ++cur;
	}
  }
}

void AddSecondAfterFirst(forward_list<string> &sflist, string first, string second) {
  auto cur = sflist.begin();
  auto pre = sflist.before_begin();
  while (cur != sflist.end()) {
    if (*cur == first) {
	  sflist.insert_after(cur, second);
	  break;
	} else {
	  pre = cur;
	  ++cur;
	}
  }

  if (cur == sflist.end())
    sflist.insert_after(pre, second);
}

template <typename T>
void DuplicateOddAndEraseEven(T t) {
  auto it = t.begin();
  while (it != t.end()) {
    if (*it % 2) {
	  //it = t.insert(it, *it++); 当it到达尾后位置的下个位置时，会进入t.erase(it)，产生非法删除越界的数据，导致崩溃
	  it = t.insert(it, *it);
	  ++it;
	  ++it;
	} else {
	  it = t.erase(it);
	}
  }
  Print(t);
}

template <>
void DuplicateOddAndEraseEven(forward_list<int> t) {
  auto pre = t.before_begin();
  auto cur = t.begin();
  while (cur != t.end()) {
    if (*cur % 2) {
	  cur = t.insert_after(cur, *cur);
	  pre = cur;
	  ++cur;
	} else {
	  cur = t.erase_after(pre);
	}
  }
  Print(t);
}

template <typename T>
void DuplicateOddAndEraseEven2(T t) {
  auto it = t.begin();
  while (it != t.end()) {
    if (*it % 2) {
	  //it = t.insert(it, *it++);
	  t.insert(it, *it++);
	  //it += 1;
	} else {
	  it = t.erase(it);
	}
  }
  Print(t);
}

void TestInsert() {
  vector<int> iv = {1,2,3,4,5,6,7,8};
  auto begin = iv.begin(),
	   end = iv.end();

  while (begin != end) {
    // 做一些处理
	// 插入新值，对begin重新赋值，否则的话它就会失效
	++begin;
	iv.insert(begin, 42);
    ++begin;
  }

}

void TestInsert934() {
  vector<int> vi = {1,2,3,4,5,6,11,23,15,24,26, 28, 31};
  auto iter = vi.begin();
  while (iter != vi.end()) 
    if (*iter % 2)
	  iter = vi.insert(iter, *iter);
    ++iter;
}
