#include "test_array.h"
#include <iostream>

using namespace std;

void test_multi_array()
{
	cout << endl;
	cout << "Test_multi_array with three print for ia array." << endl;
	

	constexpr int row = 3, col = 4;
	int ia[row][col] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	

	cout << "The first: "; // 使用引用更加高效，利用范围for，进行遍历
	for (int (&p)[col] : ia) // 元素为容量为col的数组，元素类型为int
		for (int &q : p)
			cout << q << ' ';
	cout << endl;


	cout << "The second: ";
	for (size_t i = 0; i < row; i++)	// 下标
		for (size_t j = 0; j < col; j++)
			cout << ia[i][j] << ' ';
	cout << endl;


	cout << "The third: ";
	for (int(*p)[col] = ia; p != ia + row; ++p) // 迭代器
		for (int *q = (*p); q != *p + col; ++q)
			cout << *q << ' ';
	cout << endl;
}


void test_multi_array_using()
{
	cout << endl;
	cout << "Test_multi_array with three print for ia array." << endl;


	constexpr int row = 3, col = 4;
	int ia[row][col] = { 0,1,2,3,4,5,6,7,8,9,10,11 };


	cout << "The first: "; // 使用引用更加高效，利用范围for，进行遍历
	for (int(&p)[col] : ia) // 元素为容量为col的数组，元素类型为int
		for (int& q : p)
			cout << q << ' ';
	cout << endl;


	cout << "The second: ";
	for (size_t i = 0; i < row; i++)	// 下标
		for (size_t j = 0; j < col; j++)
			cout << ia[i][j] << ' ';
	cout << endl;


	cout << "The third: ";
	for (int(*p)[col] = ia; p != ia + row; ++p) // 迭代器
		for (int* q = (*p); q != *p + col; ++q)
			cout << *q << ' ';
	cout << endl;
}


