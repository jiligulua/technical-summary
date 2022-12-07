#include <iostream>

struct SalesData {};

int main()
{
	int i = 0, &r1 = i;
	double d = 0, &r2 = d;

	r2 = 3.1415926;
	r2 = r1;
	i = r2;
	r1 = d;

	int j = 42;
	int *p = &j;

	*p = *p * *p;
	std::cout << "*p " << *p << std::endl;
	std::cout << "*p1 = *p1 * *p1 = " << *p << std::endl; 


	int *pj = &j;
	int **ppj = &pj;

	std::cout << "j=" << j << "; pj content " << *pj << "; ppj raw object is " << **ppj << std::endl;


	const int &ri2 = 42;
	const int &r3 = 0;

	int i6, *const cp6 = &j;

	int null = 0;
	int *p666666 = &null;

	return 0;

}
