#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <iterator>

using namespace std;

template<typename T>
void print(const T &v)
{
	
	for (auto item : v)
		cout << item << " ";
	cout << endl;
}

int main()
{
	vector<int> v = {2,3,4,5,6,7};
	vector<int> v2 = {10, 11, 12, 14};

	//v.assign(v2.begin() + v2.size()/2, v2.end());
	v.clear();
	v.insert(v.end(), v2.begin() + v2.size()/2, v2.end());
	print(v);

	decltype(v2) v3;
	v3.assign({1,2,3,4,5});
	print(v3);

	ifstream dataFile("str.txt");
	istream_iterator<string> dataBegin(dataFile);
	istream_iterator<string> dataEnd;
	list<string> data(dataBegin, dataEnd);

	print(data);
	
	return 0;
}
