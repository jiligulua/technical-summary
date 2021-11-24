#include "test_string.h"
#include "test_vector.h"
#include "test_array.h"
#include "test_operator.h"

int main()
{
    TestArray ta;
    ta.Test();

    // TestVector tv;
    // tv.Test();

    // TestString ts;
    // ts.Test();
    mars::test_operator();
}