#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int main(int argc, char* argv[])
{
	ifstream fin("./test.txt");
	istream_iterator<string> input_iter(fin), eof;
	vector<string> vstr(input_iter, eof);

	ostream_iterator<string> out_iter(cout, " ");
	copy(vstr.cbegin(), vstr.cend(), out_iter);
	cout << endl;
	return 1;
}
