#include <type_traits>
#include <iostream>
#include <typeinfo>
#include <functional>
#ifndef _MSC_VER
#include <cxxabi.h>
#endif
#include <vector>

using namespace std;

#define WCJNAME(x) (abi::__cxa_demangle(typeid(x).name(), nullptr, nullptr, nullptr))

template<typename T>
typename std::remove_reference<T>::type *Create()
{
	typedef typename std::remove_reference<T>::type U;
	return new U();
}

using max_size_t = std::conditional<(sizeof(long long) >sizeof(long double)), long long, long double>::type;

void func()
{
	cout << "func(): " << __FUNCTION__ << endl; 
}


void output(int x, int y)
{
	cout << x << " " << y << endl;
}

class Foo
{
public:
	void operator ()(void) {
		cout << "Foo(): " << __FUNCTION__ << endl;
	}

};



int main()
{
//	int i = 1;
//	int &j = i;
//
//	int * q = Create<int &>();
//	
	cout << WCJNAME(max_size_t) << std::endl;

	//printf("%s\n", abi::__cxa_demangle(typeid(1.0).name(), nullptr, nullptr, nullptr)); 
	printf("%s\n", WCJNAME(1)); 

	func();

	Foo foo;
	foo();


	std::bind(output, 1, 2)();
	std::bind(output, 1, std::placeholders::_1)(8);
	std::bind(output, 2, std::placeholders::_2)(4, 6);
	std::bind(output, 2, std::placeholders::_3)(4, 6, 8);
	

	int a = 0;
	auto f = [a] () mutable { return a++; };
	
	std::function<int(void)> f2 = std::bind([](int a) { return a; }, 123);

	cout << " f2: " << f2() << endl;



	cout << "Test range-based for:\n";

	std::vector<int> arr = {1, 2, 3, 4, 5};
	for (auto val : arr) {
		cout << val << endl;
		arr.push_back(0);
	}

	return 0;
}
