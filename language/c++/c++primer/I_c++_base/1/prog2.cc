#include <iostream>

using namespace std;


int main()
{
	int sum = 0, val = 0;
	cout << "Enter int values for sum: \n";
	while(cin >> val) {
		sum += val;
	}

	cout << "The above int(s) numbers is: " << sum << endl;

	return 0;
}
