#include <iostream>
#include <fstream>
#include <string>
using namespace std;

istream & readFile(istream & is)
{
	string line;
	unsigned index = 0;
	while(is >> line)
	{
		cout << index++ << ":" << line << endl;
	}
//	is.clear();
	return is;
}

int main(int argc, char* argv[])
{
//	ifstream ifs("./file1.txt");

	cout << "Hi" << endl;
	cout << "Hi" << "World";
	cout << flush;
	cout << "I" << ends << "love" << ends << "you";

	int i;

	while(cin>> i)
		cout << i << " ";
	cout << endl;

	cout << "reason is: ";
	cout << cin.badbit << ends 
			<< cin.failbit << ends << ends
			<< cin.eofbit;

	cout << endl;
	readFile(cin);
	if (cin.good())
		cout << "ifstream is still valid" << endl;
	else
		cout << "ifstream is not valid" << endl;

	//readFile(ifs);  

	return 1;
}
