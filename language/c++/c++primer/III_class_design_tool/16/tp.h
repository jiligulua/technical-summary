#ifndef _TP_H_
#define _TP_H_

#include <functional>
#include <iostream>
#include <algorithm>
#include <vector>



template<typename T>
size_t countItem(const std::vector<T> &v, const T &t)
{
	return std::count(std::begin(v), std::end(v), t);
}

//------------------------------------------------------------
template<typename T>
void calc(T, int) {}

template<typename T>
void fcn(T, T) {}

template<typename T>
void f1(T, T) {}

template<typename T1, typename T2>
void f2(T1, T2)
{}

//-------------------------------------------------------------


template<unsigned N>
unsigned array_size(const char (&p1)[N])
{
	return N;
}

#endif
