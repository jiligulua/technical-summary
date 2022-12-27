#include <iostream>
#include "Sales_item.h"

int main() 
{
	Sales_item total;

	std::cout << "Input the same transs:\n";
	int num = 0;

	Sales_item trans;
	if (std::cin >> total) {
		num = 1;
		while(std::cin >> trans) {
			if (total.isbn() == trans.isbn()){
				total += trans;
				++num;
			}
			else {
				std::cout << "Isbn " << total.isbn() << " 's numbers is " << num 
						<< " total avg price is " << total.avg_price() << std::endl;
				std::clog << "The different books\n";
				total = trans;
				num = 1;
			}
		}

		std::cout << "Isbn " << total.isbn() << " 's numbers is " << num << std::endl;
	}

	return 0;
}
