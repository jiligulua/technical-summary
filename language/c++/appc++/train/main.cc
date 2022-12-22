#include <iostream>
#include "singleton.h"
#include "testa.h"


int main()
{
	string str = "bb";
	TestA a = std::move(str);
	TestA b = str;
	Singleton<TestA>::CreateInstance("World");


	Singleton<TestA>::DestroyInstance();

	return 0;
}
