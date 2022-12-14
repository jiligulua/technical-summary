#include <iostream>
#include <vector>
#include <initializer_list>
#include <string>
#include <list>
#include "blob.h"
#include "tp.h"
#include "package_args.h"
#include "compare.h"
#include "execise_16.h"
#include "nodefault.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

extern template class vector<string>;
//template class vector<NoDefault>;
template <typename T> T calc(T, int);
template <typename T> T fcn(T, T);

int main()
{
	int ret = compare(1.0, 2.0);
	cout << ret << endl;


	char arr[] = {"Hello World!"};
	int sz = array_size(arr);
	cout << "array size is " << sz << endl;

	print(arr);

	int arr2[]= {1, 3, 4, 5, 7, 8};
	print(arr2);


	std::initializer_list<int> il = {1, 2, 3, 4, 5};
	vector<int> iv(il);
	for(auto item : iv)
		cout << item << " ";
	cout << endl;


	compare("bye", "dad");
//	compare("hi", "dad");

	double d; float f; char c;

	//calc(c, 'c');
//	calc(d, f);
//	fcn(d, f);
	int i = 0, j = 42, *p1 = &i, *p2 = &j;
	const int *cp1 = &i, *cp2 = &j;

//	f1(p1, cp1);
	f1(p1, p2);
	f1(cp1, cp2);

	f2(cp1, cp2);
	f2(p1, cp1);


	int i2 = 42;
	string s2 = "software";
	NoDefault nodefault;
	print(cout, i2, s2, 42);
	

	errorMsg(cerr, "Hello World", "I", 520, 'u');


	const char *p11 = "w hi";
	const char *p12 = "mom";
	compare(p11, p12);

	vector<double> vd = {1.0, 1.0, 2.01, 4.01};
	vector<int> vi = {1, 2, 3,4, 5, 5, 6};
//	vector<string> vstr = {"Hello", "Hello", "I", "love", "u"};

	string strHello = "Hello";

	//cout << "vd:" << countItem(vd, 1.0) << ", vi:" << countItem(vi, 5) << endl;//", vstr:" << countItem(vstr, strHello) << endl;

	cout << "Test compare1::";
	cout << "compare result:" << compare1(p11, p12) 
			<< ", p11 address: " << &p11 
			<< ", p12 address: " << &p12 << endl;;

	cout << "p11 < p12 = " <<  (p11 < p12 ? -1 : 1) << endl;

	cout << "hello < world ? The result is " << compare1("hello", "world") << endl;
	cout << "hello < hi world ? The result is " << compare1("hello", "hi world") << endl;


	vector<int> vi2 = {1, 2, 3, 4, 5, 6, 7, 8};
	auto it = find_y(vi2, 5);
	cout << "find_y(vi2, 5), the result is " << (it == vi2.end() ? -1 : *it) << endl;
	it = find_y(vi2, 15);
	cout << "find_y(vi2, 15), the result is " << (it == vi2.end() ? -1 : *it) << endl;


	// test 16.4
	list<string> lstr = {"hello", "world", "god"};
    //lstr.emplace_back("hello");
    //lstr.emplace_back("world");
    //lstr.emplace_back("god");

	string hello("hello");
	auto it2 = find_y(lstr, hello);
	cout << "find_y(lstr, \"Hello\")? " << (*it2 == hello ? "yes" : "no") << endl;
	string god("gods");
	it2 = find_y(lstr, god);
	cout << "find_y(lstr, \"god\")? " << (*it2 == god ? "yes" : "no") << endl;
	
	// test 16.5
	const char arr1[] = {'a', 'b'};
	const string arr22[] = {"Hello", "world"};
	const int arr3[] = {1,2,3,4,5};
	cout << "test 16.4-------------------" << endl;
	print_y(arr1);
	print_y(arr22);
	print_y(arr3);

	// test 16.6
	cout << "test 16.6-------------------" << endl;
	for_each(begin_y(arr1), end_y(arr1), [](const char i) { cout << i << ' '; });
	cout << endl;

	// 16 Sample	
	Blob<string> articles = {"a", "an", "the"};

	return 0;
}
