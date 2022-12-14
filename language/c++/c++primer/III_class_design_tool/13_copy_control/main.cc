#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "has_ptr.h"
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::set;


class Person{
 public:
  Person() = default;
  Person(string n, string add) 
		: name(n)
		, address(add) {}

 private:
	string name;
	string address;
};

class SalesData {
  public:
	SalesData() { cout << "SalesData()" << endl;}
	SalesData(const SalesData &a) { cout << "SalesData(const SalesData &a)" << endl; }
	~SalesData() { cout << "~SalesData()" << endl; }
  int *p;  
  int a[4] {1,2,3,4}; 
};

void CallSalesData(SalesData a) {
  cout << __func__ << endl;
  SalesData b = a;
}

int main() {
//
//  Person p1;
//
//  SalesData sd;
//  sd.a[2] = 100;
//
//  SalesData sd2(sd);
//
//  sd2.a[2] = 1;
//
//  cout << sd.a[2] << " " << sd2.a[2] << endl;
//
//  CallSalesData(sd);
//
  HasPtr hp("Hello");
  HasPtr hp2("ABC");

  vector<HasPtr> vhp;
  vhp.push_back(hp);
  vhp.push_back(hp2);

  cout << "Begin to sort" << endl;
  std::sort(vhp.begin(), vhp.end());
  cout << "End to sort" << endl;
  for (auto i : vhp) 
	cout << *i << " ";
  cout << endl;


  cout << "Test set ..." << endl;
  set<int> s {1,2,6,5,4,3,2,1};
  for (auto i : s)
	cout << i << " ";
  cout << endl;

}
