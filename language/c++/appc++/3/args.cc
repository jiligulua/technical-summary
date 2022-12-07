#include <iostream>
#include "args.h"
#include <string>
#include "person.h"
#ifndef _MSC_VER
#include <cxxabi.h>
#endif
#include <typeinfo>

using namespace std;


int main()
{
		f();
		f(1);
		f(2.1, 3, 45);

		//print(1, 2, "Hello", "World", "I", "love", "you", "520");
		print(1, 2, "Hello", "World", "I", "love", "you", "520");

		MySum<Person, Animal, int> sum;
		cout << "sizeof sum is: " << sum.value << endl;	


		using T = MakeIndexes<3>::type;
		cout << abi::__cxa_demangle(typeid(1.0).name(), nullptr, nullptr, nullptr) << endl;
		
		return 0;
}
