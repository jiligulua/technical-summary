// algo.cpp: 定义应用程序的入口点。
//

#include "algo.h"
#include <algorithm>
#include "test.h"

using namespace std;


int main()
{
	mars::Test test;
	test.testSort();

	string str = "I,love,you";
	auto iter = find(str.crbegin(), str.crend(), ',');
	cout << "riter comma: " << *iter << endl;
	auto base_iter = iter.base();
	cout << "r-riter comma: " << *base_iter++ << endl;
	while (base_iter != str.cend())
		cout << *base_iter++ << " ";
	cout << endl;

	for_each(str.crbegin(), str.crend(), [](char c) { cout << c; });
	cout << endl;
	vector<int> ivec = { 1, 2, 4, 5, 6, 7, 8, 9, 22 };
	auto count = ivec.size();

	while (count--)
		cout << *(ivec.cbegin() + count) << " ";

	cout << endl;
	list<int> li = { 1, 2, 0, 4, 5, 6, 0, 19, 43, 0, 3 };
	auto last_zero = find(li.crbegin(), li.crend(), 0);
	ostream_iterator<int> ostr_iter(cout, " ");
	//copy(last_zero, li.cend(), ostr_iter);
	for_each(last_zero, li.cend(), [](int i) { ostr_iter = i; });
	cout << endl;
	cout << "last zero index is: " << *last_zero << endl;

	return 0;
}
