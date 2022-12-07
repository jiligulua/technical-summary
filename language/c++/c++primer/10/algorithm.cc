#include <algorithm>
#include <iostream>
#include <deque>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <numeric>
#include "common.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

void TrainIstreamIterator() {  
  Tips(__func__);
  std::istream_iterator<int> in_iter(cin), eof;
  std::cout << std::accumulate(in_iter, eof, 0) << endl;
}

void Do1028() {
  Tips(__func__);
  vector<int> ivec {1,2,3,4,5,6,7,7,8,9,9};
  vector<int> ivec1;
  std::deque<int> idq;
  std::list<int> il;
  
  std::copy(std::begin(ivec), std::end(ivec), std::back_inserter(ivec1));
  Print(ivec1);
  
  std::copy(ivec.begin(), ivec.end(), std::front_inserter(idq));
  Print(idq);

  std::copy(ivec.begin(), ivec.end(), std::inserter(il, il.end()));
  Print(il);
}

void TestInerterIterator() {
  Tips(__func__);
  vector<int> ivec = {1,1,2,3,3,3,4,5,6,7,};
  std::list<int> il;
  std::unique_copy(ivec.begin(), ivec.end(), std::back_inserter(il));
  Print(il);
}

void biggies(vector<string> &words, vector<string>::size_type sz) {
  std::stable_sort(words.begin(), words.end());
  auto unique_end = std::unique(words.begin(), words.end());  
  words.erase(unique_end, words.end());
  std::stable_sort(words.begin(), words.end(), [](const string& left, const string& right) { return left.size() < right.size(); });
  auto first_word = find_if(words.cbegin(), words.cend(), [sz](const string &word) { return word.size() >= sz; });
  std::for_each(first_word, words.cend(), [](const string & word) { std::cout << word << " "; });
  std::cout << std::endl;
}

void biggies2(vector<string> &words, vector<string>::size_type sz) {
  auto part_end = std::stable_partition(words.begin(), words.end(), [sz](const string &str){ return str.size() >= sz; });
  auto unique_end = std::unique(words.begin(), part_end);
  std::for_each(words.begin(), unique_end, [](const string& str) { cout << str << " "; });
  std::cout << std::endl;
}



void TestLambda() {
  vector<int> ivec = {1,2,3,4,3,2,34,3,2,43,53,23,42,43};
  auto f = [] {
    int a;
	int b;
	int c = a * b;
	bool flag;
	return flag;

  };

  auto add = [](int i, int j) { return i + j;};
  int age = 18;
  auto total_age = add(4, 7);
  auto AddAge = [total_age](int i) { return i + total_age; }; 
  auto added_age = AddAge(42);
  cout << "children total age is " << total_age << " after add Dad's age is " << added_age << endl;
}

bool TestPartition() {
  vector<string> svec = {"Hello", "world", "morning", "afternoon", "I", "love", "you"}; 
  auto end_it = std::partition(svec.begin(), svec.end(), [](string s){ return s.size() >= 5;});
  auto it = svec.cbegin();
  while (it != end_it) {
    cout << *it << " ";
	++it;
  }
  cout << endl;
}

void TestSort() {
  vector<int> ivec = {12,3,4,53,43,22,5,7,6,56,43};
  std::sort(ivec.begin(), ivec.end(), [](int a, int b){ return a > b;});
  Print(ivec);

}

void TestUnique() {
  string word;
  vector<string> svec;
  while (cin >> word)
    svec.push_back(word);

  Print(svec);
  cout << "svec size " << svec.size() << endl;
  std::sort(svec.begin(), svec.end());
  auto end_iter = std::unique(svec.begin(), svec.end());
  svec.erase(end_iter, svec.end());
  Print(svec);
  sort(svec.begin(), svec.end(), [](string left, string right){ return left.size() < right.size(); });

  Print(svec);
  cout << "svec size " << svec.size() << endl;
}

void TestFillN() {
  vector<int> ivec(10);
  ivec.reserve(10);
  fill_n(ivec.begin(), ivec.size(), 42);
  Print(ivec);
}

void TestForEach() {
  Tips(__func__);
  vector<int> ivec = {1,2,3,4,5,6};
  std::for_each(ivec.begin(), ivec.end(), [](int &i) { i *=i; });
  Print(ivec);
}

int main() {
  TestForEach();
  TrainIstreamIterator();
  Do1028();
  TestInerterIterator();
  vector<string> svec = {"x", "a", "A", "World", "Hello", "I", "love", "school", "I", "love", "yours"};
  vector<string>::size_type sz = 5;
  biggies(svec, sz);
  biggies2(svec, sz);
  TestLambda();
  TestPartition();
  TestSort();
  TestFillN();
  TestUnique();
}

