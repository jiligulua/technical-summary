#include <iostream>


int main()
{
	unsigned u = 10, u2 = 42;
	std::cout << u2 - u << std::endl;
	std::cout << u - u2 << std::endl;

	int i = 10, i2 = 42;
	std::cout << i2 - i << std::endl;
	std::cout << i - i2 << std::endl;
	std::cout << i - u << std::endl;
	std::cout << u - i << std::endl;

	std::cout << "3e3=" << 3e3  << std::endl;
	std::cout << "3e0=" << 3e0  << std::endl;
	std::cout << "0.=" << 0. << std::endl;
	std::cout << ".001=" << .001 << std::endl;
//	std::cout << '\a' << std::endl;
	int month = 07;
	std::cout << "month " << month << std::endl;
	std::cout << "1024.0F=" << 1024.0F << std::endl;
    std::cout << "3.14e1L=" << 3.14e1L << std::endl;
	std::cout << "3.14L=" << 3.14L << std::endl;	
	std::cout << "Who goes with F\145rgus?\012" << std::endl;
	std::cout << "\60\x4d" << std::endl;
	std::cout << '\60' << '\t' << '\x4d' << std::endl;


	double Double = 3.14;
	int _;


	int j = 100, sum = 0;
	for (int j = 0; j != 10; ++j) {
		sum += j;
	}

	std::cout << "j " << j << " sum " << sum << std::endl;

	return 0;
}
