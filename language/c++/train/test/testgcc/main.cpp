#include <iostream>
#include <stdlib.h>
#include "operator.h"
#include "time_util.h"

using namespace std;


int main(int argc, char* argv[])
{

	cout << "Command parameter count is: "<< argc << endl;
	for(int i = 0; i < argc; ++i) 
		cout << i << " " << argv[i] << endl;
	
	if (argc != 3) {
		cout << "parameter count error! " << endl;
		return 0;
	}

	int a = atoi(argv[1]);
	int b = atoi(argv[2]);

	cout << a << " + " << b << " = " << add(a, b) << endl;

	TimeUtil timeutil;
	cout << "Timestamp: " << timeutil.GetTimestamp() << endl;
	return 0;
}
