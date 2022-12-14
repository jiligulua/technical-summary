#ifndef _COMPARE_H_
#define _COMPARE_H_

#include <functional>
#include <string.h>
#include "package_args.h"


template <typename T>
int compare1(const T &v1, const T &v2)
{
	if (std::less<T>()(v1, v2)) return -1;
	if (std::less<T>()(v2, v1)) return 1;
	return 0;
}

template <unsigned M, unsigned N>
int compare1(const char (&p1)[M], const char (&p2)[N])
{
	print("template <unsigned M, unsigned N>");
	return strcmp(p1, p2);
}

template <unsigned N>
int compare1(const char (&p1)[N], const char (&p2)[N])
{
	print("template <unsigned N>");
	return strcmp(p1, p2);
}

//template <typename T, typename F = less<T>>
//int compare1(const T &v1, const T &v2, F f = F()) {
//  if (f(v1, v2)) return -1;
//  if (f(v2, v1)) return 1;
//  return 0;
//}

#endif

