#include "TutorialConfig.h"
#ifdef USE_MYMATH
	#include "mysqrt.h"
#endif

#include <iostream>
#include <math.h>
#include <string>

using namespace std;


int main(int argc, char* argv[])
{
	
	if (argc < 2){
		cout << "Usage: " << argv[0] << " number";
		return 0;
	}
	
	long baseNum = stol(argv[1]);
	
	if (argc == 2)
		cout << "tips: " << argv[1] << endl;
	
#ifdef USR_MYMATH
	cout << "use mymath: the squre of " << baseNum <<" is " << myquare(baseNum)) << endl;
#else
	cout << "use system: the squre of " << baseNum <<" is " << pow(baseNum, 2) << endl;
#endif

	cout << "Usage: " << argv[0] << " number" << endl;
	
	return 1;
}