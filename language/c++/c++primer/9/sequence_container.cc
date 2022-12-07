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

void TestVectorGross() {
  vector<int> vi;
  std::cout << "size: " << vi.size() << ", capacity: " << vi.capacity() << std::endl;
  for (vector<int>::size_type i = 0; i < 100; ++i) {
    vi.push_back(i);
    std::cout << "size: " << vi.size() << ", capacity: " << vi.capacity() << std::endl;
  }
}

void TestVector939() {
  std::cout << "Test Vector 939" << std::endl;
  vector<string> svec;
  std::cout << "size: " << svec.size() << ", capacity: " << svec.capacity() << std::endl;
  svec.reserve(1024); 
  std::cout << "size: " << svec.size() << ", capacity: " << svec.capacity() << std::endl;

  string word;
  while (std::cin >> word) 
    svec.push_back(word);
   
  Print(svec);
  std::cout << "size: " << svec.size() << ", capacity: " << svec.capacity() << std::endl;
  svec.resize(svec.size() + svec.size()/2, "export");
  //svec.resize(svec.size()/2);
  //svec.resize(svec.size()/2, "export");
  std::cout << "size: " << svec.size() << ", capacity: " << svec.capacity() << std::endl;
  Print(svec);
}

void TestReplace943(string s, const string & old_value, const string & new_val) {
  
}

int main() {
  vector<string> v1 = {"Hello", "World", "I", "love", "you"};
  vector<string> v2 = {"en"};
  v1 = v2;  
  Print(v1);

  vector<int> vi = {1,2,3,4,5,6,7};
  bool found = FindItem(vi.cbegin(), vi.cend(), 6);
  auto iter = FindItemIterator(vi.cbegin(), vi.cend(), 6);
  std::cout << "iter content is " << *iter << std::endl;

  list<deque<int>> ldi;

  int a = -1;
  unsigned b = 2;
  if (a > b) 
    std::cout << "a(" << a << ") > " << "b(" << b << ")" << std::endl;
  else
    std::cout << "a(" << a << ") < " << "b(" << b << ")" << std::endl;
  
  vector<int> vi2 = {1,2,3,4,5,6,7,8,9,10};
  vector<double> vd(vi2.begin(), vi2.end());
  Print(vd);


  list<int> li = {1,2,3,4,5,6};
  Print(li);

  vector<double> vd2(li.begin(), li.end()); 
  Print(vd2);

  list<int> li2 = {1};
  li = li2;
  Print(li);

  array<int, 42> a1 = {1,2, 3,4};
  array<int, 42> a2 = {4};
  Print(a1);
  Print(a2);


  li.assign(li.cbegin(), ++li.cbegin());
  Print(li);
  std::cout << li.size() << std::endl;

  list<const char*> lic = {"Hello", "Automatic", "I", "love", "you"};
  vector<string> vstr;
  vstr.assign(lic.begin(), lic.end());
  Print(vstr);
  
  if (vi == vi2) 
    std::cout << "vi == vi2" << std::endl;
  else
    std::cout << "vi != vi2" << std::endl;

  vi.assign({1,2,3,4,5,6});
  li.assign({1,2,3,4,5,6});
  CompareDifContainer(vi, li);

  li.push_back(7);

  vector<string> vstr2 = {"wu", "chao", "jiang"};
  vstr2.insert(vstr2.begin(), vstr2.begin(), vstr2.end());
  Print(vstr2);
  //Exercise918();

  vector<int> ivec = {1,2,3,5,3,2,4,4};
  Print(ivec);
  DoubleSpecifiedNumber(ivec, 2);
  Print(ivec);
  try {
	std::cout << "ivec size " << ivec.size() << ", max size " << ivec.max_size() << std::endl;
    int a = ivec[111];
	Print(ivec);
    //ivec.at(10);
  } catch(const std::exception & e) {
    std::cout << "EXCEPTION: " <<  e.what() << std::endl;
  }

  vector<string> svec(1, "Hello");
  std::cout << "Only one item: " << svec.front() << " " << *svec.begin() << " " << svec.back() << " " << (*--svec.end()) << std::endl;
  Print(svec);
  
  vector<string> svec2;
  //string s11 = *--svec2.end();
  //svec2[0];
  //svec2.at(0);
  list<int> ilist = {1,2,3,4,5,6,7,8,9,0};
  Print(ilist);
  auto elem1 = ilist.begin();
  auto elem2 = ilist.end();
  ilist.erase(elem1, elem2);
  Print(ilist);
  
  int ia[] = {0, 1,1,2,3,5,8,13,21,55,89};
  list<int> ilista(ia, ia+sizeof(ia)/sizeof(int));
  vector<int> iveca(ia, ia+sizeof(ia)/sizeof(int));
  RemoveOddItem(ilista);
  Print(ilista);
  RemoveEvenItem(iveca);
  Print(iveca);

  forward_list<int> iflist = {1,2,3,4,5,6,7,8,9,0,12,12,32,43,232,4,42,5};
  Print(iflist);
  RemoveOddItemFromForwardList(iflist);
  Print(iflist);
  
  forward_list<string> sflist = {"Hello", "World", "I", "love", "you"};
  Print(sflist);
  AddSecondAfterFirst(sflist, "World", "!");
  Print(sflist);
  AddSecondAfterFirst(sflist, ".", "yeah");
  Print(sflist);

  vector<string> svec3(25);
  std::cout << "svec3 size: " << svec3.size() << " ";
  svec3.resize(100);
  std::cout << "svec3.resize(100) svev3.size: " << svec3.size() << std::endl;
  
  vector<int> ivec_add = {1,2,3,4,5,6,7,8,9};
  Print(ivec_add);
  auto it = ivec_add.begin();
  while (it != ivec_add.end()) {
	++it;
	it = ivec_add.insert(it, *it * *it);
	++it;
  }
  Print(ivec_add);

  vector<int> ivec_odd_even = {1,2,3,4,5,6,7,8,9,0,};
  ivec_odd_even.insert(ivec_odd_even.end(), 10);
  Print(ivec_odd_even);
  DuplicateOddAndEraseEven(ivec_odd_even); 

  list<int> ilist_odd_even = {1,2,3,4,5,6,7,8,9,0,};
  Print(ilist_odd_even);
  DuplicateOddAndEraseEven(ilist_odd_even); 
  
  forward_list<int> iflist_odd_even = {1,2,3,4,5,6,7,8,9,0,};
  Print(iflist_odd_even);
  DuplicateOddAndEraseEven(iflist_odd_even); 

  vector<int> ivec_erase = {1,2,3,4,5,6,7,8,9};
  Print(ivec_erase);
  DuplicateOddAndEraseEven(ivec_erase);

  //TestInsert(); // It will crash.
  //TestInsert934(); // deadloop always insert the first odd number
  TestVectorGross();
  TestVector939();

  vector<char> cvec = {'h', 'e', 'l', 'l', 'o'};
  Print(cvec);
  string str3(cvec.begin(), cvec.end());
  std::cout << "to string: ";
  Print(str3);
  str3.resize(100);
  std::cout << "str3 size " << str3.size() << std::endl;
  const char *cp = "Stately, plump Buck";
  string s;
  s.assign(cp, 7);
  s.insert(s.size(), cp + 7);


}
