#include <iostream>
#include <memory>
#include <vector>
#include <string>

using std::shared_ptr;
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::make_shared;

using VecStr = vector<string>;

void printData(shared_ptr<VecStr> sptr)
{
	if (!sptr || sptr->empty())
		return;

	for (auto p : (*sptr))
		cout << p << " ";

	cout << endl;
}

shared_ptr<VecStr> readData(shared_ptr<VecStr> sptr)
{
	string str;
	getline(cin, str, '#');
	sptr->push_back(str);


	return sptr;
}	

shared_ptr<VecStr> getSptr()
{
	auto sp = make_shared<VecStr>();
	return sp;
}

int main()
{
	auto sp = getSptr();
	auto data = readData(sp);
	printData(data);
	return 0;
}
