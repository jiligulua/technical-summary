#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "generic_algorithm.h"
#include <algorithm>
using namespace std;


bool haveContinueCountChar(const string &str, unsigned count)
{
	string temp(str);
	auto it = partition(temp.begin(), temp.end(), [](const auto & ch)->bool{
								return ( ('a' < ch && ch < 'z') || 
									('A' < ch && ch < 'Z'));
							});
	cout << "src: " << str << " ,modify: " << temp << endl;
	return (it - temp.cbegin()) >= 5;
}

void elimDups(vector<string> &word)
{
	sort(word.begin(), word.end());

	//sort(word.begin(), word.end(), [](const string &lhs, const string &rhs){
	//	return lhs.size() < rhs.size();
	//});
	auto end_unique = unique(word.begin(), word.end());
	word.erase(end_unique, word.end());
}

int main(int argc, char* argv[])
{
	vector<int> ivec = {1, 2, 3, 4, 8, 4, 42, 42, 42,5, 6, 7};
	list<string> slist = {"Hello", "World", "Hello", "I", "love", "you"};

	GenericAlgo<vector<int>, int> ga;
	GenericAlgo<list<string>, string> ga2;

	cout << ga.getCount(ivec, 42) << endl;
	cout << ga2.getCount(slist, "Hello") << endl;

	vector<string> ivec2 = {"ae", "dl", "bo", "corld", "eor", "ford"};
	elimDups(ivec2);
	for(const auto & item : ivec2)
		cout << item << " ";
	cout << endl;

	string st2 = "H23w234g2345gety";
	if (haveContinueCountChar(st2, 5))
		cout << "has least 5 items";
	return 0;
}
