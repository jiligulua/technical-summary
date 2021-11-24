#include "test_thread.h"
#include "test_deprecated.h"

int main()
{
    TestThread tt;
    tt.run();

    cpp11::test_deprecated();
}