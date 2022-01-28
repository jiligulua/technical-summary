#include "test_dp.h"
#include "dp_triangle.h"
#include "dp_fibonacci.h"

namespace mars
{
    void testDp()
    {
        // testTriangle();
        testFibonacci();
    }   

    void testTriangle()
    {
        DpTriangle triangle;
        triangle.run();
    }

    void testFibonacci()
    {
        Fabonacci fabonacci;
        fabonacci.run();
    }
}