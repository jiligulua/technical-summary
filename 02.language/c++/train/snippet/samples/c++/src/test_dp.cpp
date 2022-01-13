#include "test_dp.h"
#include "dp_triangle.h"

namespace mars
{
    void testDp()
    {
        testTriangle();
    }   

    void testTriangle()
    {
        DpTriangle triangle;
        triangle.run();
    }
}