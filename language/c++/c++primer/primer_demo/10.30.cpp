#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>


using namespace std;

void test1031()
{
	
	istream_iterator<int> input_iter(cin), eof;
	vector<int> vi(input_iter, eof);
	sort(vi.begin(), vi.end());
	ostream_iterator<int> output_iter(cout, " ");
	//copy(vi.cbegin(), vi.cend(), output_iter);
	unique_copy(vi.cbegin(), vi.cend(), output_iter);
}


int main(int argc, char* argv[])
{
	test1031();
	return 1;
}

