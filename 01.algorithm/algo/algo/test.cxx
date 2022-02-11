#include "test.h"
#include "sort.h"
#include <iostream>
#include <algorithm>

using namespace std;


namespace mars
{
	void Test::testSort()
	{
		int arr[] = { 4, 3, 8, 6,7,8, 9, 11, 22, 15 };
		int len = sizeof(arr) / sizeof(int);
		print(arr, len);

		Sort s;
		//s.bubbleSort(arr, len);
		//s.quickSort(arr, 0, len - 1);
		//s.insertSort(arr, len);
		s.shellSort(arr, len);

		print(arr, len);

	}

	void Test::print(int arr[], int len)
	{
		for_each(arr, arr + len, [](int i) 
		{ 
			cout << i << " "; 
		});

		cout << endl;
	}

}