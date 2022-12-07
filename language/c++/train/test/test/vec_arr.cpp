#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
	int iarr[] = {1, 2, 3, 4, 5, 6};
	vector<int> ivec(begin(iarr), end(iarr));
	for_each(ivec.begin(), ivec.end(), [](int item){
					cout << item << " ";
					});	

	cout << endl;

	int iarr2[10] = {0};
	int len = sizeof(iarr2) / sizeof(int);
	cout << "len: " << len << endl;
	if(len >= ivec.size())
	{
		auto iter = ivec.begin();
		int i = 0;
		while(iter != ivec.end())
		{
			*(iarr2+i) = *iter;
			iter++;
			i++;
		}

		cout << "\nvector to array: ";
		for(int i = 0; i < len; ++i)
			cout << iarr2[i] << " ";
		cout << endl;
	}

	return 1;
}

