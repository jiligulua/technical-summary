#include <iostream>
#include <cstdlib>
#include "TutorialConfig.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cout << argv[0] << " Version" << Tutorial_VERSION_MAJOR << "."
			 << Tutorial_VERSION_MINOR << endl;
		cout << "Usage: " << argv[0] << " number" << endl;
		
		return 1;
	}
	
	const double inputValue = std::stod(argv[1]);
}