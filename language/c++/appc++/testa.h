#ifndef __TestA_H__
#define __TestA_H__

#include <iostream>
#include <string>

using namespace std;

struct TestA
{
	TestA(const string &);
	TestA(string &&);
};

#endif//__A_H__

