#include "TutorialConfig.h"
#ifdef USE_MYMATH
	#include "mysqrt.h"
#endif

#include <iostream>
#include <math.h>

using namespace std;


int main(int argc, char* argv[])
{
#ifdef USR_MYMATH
	cout << "use mymath: the squre of 8 is: " << myquare(8) << endl;
#else
	cout << "use system: the squre of 8 is: " << pow(8, 2) << endl;
#endif

	return 1;
}