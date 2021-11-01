#include <iostream>
#include "../../include/thread/test_thread.h"

using namespace std;

TestThread::TestThread(void)
{}

TestThread::~TestThread(void)
{}

void TestThread::run() 
{
    cout << "Hello TestThread class";
}

int main() {
    TestThread tt;
    tt.run();
}