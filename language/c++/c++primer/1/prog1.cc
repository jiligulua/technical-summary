#include <iostream>

int main()
{
	std::cout << "I'm from cout\n";
	std::cout << "Hello World!\n";
	std::cerr << "I'm from cerr\n";
	std::clog << "I'm from clog\n";

	std::cout << "Input two numbers:\n";
	/*
	int v1=0, v2=0;
	std::cin >> v1 >> v2;
	std::cout << "v1 + v2 = " << v1+v2 << std::endl;
	std::cout << "v1 * v2 = ";
	std::cout << v1 * v2;
	std::cout << std::endl;
	

	int ival = 9;
	while(ival > 0)
	{
		std::cout << ival << " ";
		--ival;
	}
	std::cout << std::endl; 
*/
	int v1 =0, v2 =0;
	if (std::cin >> v1 >> v2){
		while(v1 - v2 != 0)
		{
			if (v1 - v2 > 0)
			{
				--v1;
			}
			else
			{
				++v1;
			}

			if (v1 !=  v2)
				std::cout << v1 << " ";
		}
	} 
	else {
		std::cerr << "ERROR: cin input error\n";
	}

	return 0;
}
