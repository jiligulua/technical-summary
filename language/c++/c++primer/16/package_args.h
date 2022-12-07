#ifndef _PACKAGE_ARGS_H
#define _PACKAGE_ARGS_H

#include <iostream>
#include <functional>
#include <sstream>

using namespace std;

template<typename T>
string debug_rep(const T &t)
{
		ostringstream ret;
		ret << t;
		return ret.str();
}

template<typename T>
string debug_rep(T *p)
{
		ostringstream ret;
		
		ret << "Pointer: " << p;
		if (p)
			ret << " " << debug_rep(*p);
		else
			ret << "nullptr";
		
		return ret.str();
}

template<typename T, unsigned N>
void print(const T (&p)[N])
{
    for(auto item : p)
        std::cout << item << " ";
    std::cout << std::endl;
}

template<typename T>
ostream &print(ostream &os, const T &t) 
{
		return os << t << endl;;
}

template<typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args&... rest)
{
		os << t << ", ";
		return print(os, rest...);
}

template<typename... Args>
ostream &errorMsg(ostream &os, const Args&... rest)
{
		return print(os, debug_rep(rest)...);
}


template<typename... Args>
void g(Args... args)
{
		cout << sizeof...(Args) << endl;
		cout << sizeof...(args) << endl;
}


template<typename T>
int compare(const T &a, const T &b)
{
    if (std::less<T>()(a, b)) return -1;
    if (std::less<T>()(b, a)) return 1;
    return 0;
}


template<>
int compare(const char* const &p1, const char* const &p2)
{
	cout << "compare specified template" << endl;
	return 0;
}

#endif
