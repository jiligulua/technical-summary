#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

int main()
{
	int sz[4] = {1,2,3,4};
	int *p1 = &sz[0];
	int *p2 = &sz[1];
	cout << p2 - p1 << endl;
	cout << p2 + p1 << endl;

//	vector<int> ivec(10,0);
	
//	for (unsigned i = 0; i < 10; ++i)
//		ivec.push_back(i);
//
//	auto end = ivec.begin() + 15;
//	if (ivec.end() == end) 
//		cout << "The end iterator is the off-the-ed iterator\n";
//	else
//		cout << "Not the off-the-end iterator\n";
//
//
//
//	int score[10];
//	for (auto i : score)
//		cout << i << " ";
//	cout << endl;

//	vector<unsigned> scores(11, 0);
//	auto beg = scores.begin();
//	unsigned grade;
//	while(cin >> grade) {
//		if (grade <= 100) {
//			(*(beg + grade/10))++;
//		}
//
//	}
//
//	cout << endl;
//	for(auto i : scores)
//		cout << i << " ";
//
//	cout << endl;

	return 0;
}
