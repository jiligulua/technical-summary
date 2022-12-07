#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


int main(int argc, char* argv[])
{
	cout << "Hello, I am from ostream";
	
	string inname;
	string outname;
	if (argc == 3)
	{
		inname = argv[1];
		outname = argv[2];
	}
	else
	{
		cerr << "argc is: " << argc << endl;
	}

	ifstream in;
	in.open(inname);
	string line;
	vector<string> svec;
	if (in)
		while(in >> line)
			svec.push_back(line);

	ofstream out;
	out.open(outname, ofstream::app);
	for(auto item : svec)
		out << item;

	for(auto item : svec)
		cout << item << endl;


	return 1;
}
