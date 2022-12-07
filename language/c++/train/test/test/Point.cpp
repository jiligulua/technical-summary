#include "Point.h"

namespace pt
{
    void printOffset()
    {
        printf("&Base1::val1 = %p\n", &Base1::val1);
        printf("&Base2::val2 = %p\n", &Base2::val2);
        printf("&Derived::val1 = %p\n", &Derived::val1);
        printf("&Derived::val2 = %p\n", &Derived::val2);
        printf("&Derived::val3 = %p\n", &Derived::val3);
    }

    void func1(int Derived::*dmp, Derived *pd)
    {
        pd->*dmp;
    }

    void func2(Derived *pd)
    {
        int Base2::*bmp = &Base2::val2;

        func1(bmp, pd);
    }
}