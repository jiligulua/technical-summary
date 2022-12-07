#include <iostream>
#include <string>

using namespace std;

istream & print_stream(istream &input_stream)
{
	string word;
	while (input_stream >> word) {
		cout << word << " ";
	}

//	input_stream.clear();

	return input_stream;
}

int main()
{
	cout << "Input data: " << endl;
	print_stream(cin);
	cout << "end" << endl;
	return 1;
}
