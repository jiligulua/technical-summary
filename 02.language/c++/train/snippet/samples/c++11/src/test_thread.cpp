#include <iostream>
#include "test_thread.h"

using namespace std;

TestThread::TestThread(void)
{}

TestThread::~TestThread(void)
{}

void TestThread::run() 
{
    cout << "Hello TestThread class";
}