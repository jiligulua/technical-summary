#include "base.h"
#include "test_operator.h"

namespace mars
{
    void test_operator()
    {
        test_comma();
        test_sizeof();
    }

    void test_comma()
    {
        cout << "\ntest_comma: ";
        int x = 5;
        int y = 6;
        bool flag = false;
        cout << flag ? ++x, ++y : --x, --y;
        cout << "\t";
        cout << (flag ? ++x, ++y : --y,--x);
        cout << "\t";
        cout << flag ? 8 : 9;

        vector<int> ivec(10, 0);
        vector<int>::size_type cnt = ivec.size();
        for (vector<int>::size_type ix = 0; ix != ivec.size(); ++ix, --cnt)
            ivec[ix] = cnt;

        vector<int> ivec2(10, 0);
        vector<int>::size_type cnt2 = ivec2.size();
        // 因为逗号运算符会丢弃运算对象的结果，而for循环中，并没有发送赋值，所以后置版本临时副本又会被丢弃，
        // 损失效率。所以，for循环中，使用前置版本
        for (vector<int>::size_type ix = 0; ix != ivec2.size(); ix++, cnt2--)
            ivec2[ix] = cnt2;


        cout << endl;
    }

    void test_sizeof()
    {
        cout << "test_sizeof: ";
        int x[10];
        int *p = x;
        cout << "sizeof(x) / sizeof(*x): " << sizeof(x) / sizeof(*x) << endl;
        cout << "sizeof(p) / sizeof(*p): " << sizeof(p) / sizeof(*p) << endl;
        cout << "sizeof(p): " << sizeof(p) << endl; // 64位时是8,32位时是4
        cout << "sizeof(*p): " << sizeof(*p) << endl;
        cout << "*p: " << *p << endl;
        cout << "p: " << p << endl;
        cout << "sizeof(int): " << sizeof(int) << endl;
        cout << "sizeof(char): " << sizeof(char) << endl;
        cout << "sizeof(byte): " << sizeof(byte) << endl;
        cout << "sizeof(short): " << sizeof(short) << endl;
        cout << "sizeof(short int): " << sizeof(short int) << endl;
        cout << "sizeof(long): " << sizeof(long) << endl;
        // 在c/c++中，没有规定long和int的长度具体是多少，
        // 只是规定long的长度不小于int的长度。其具体长度跟系统和编译器有关。
        cout << "sizeof(long int): " << sizeof(long int) << endl;
        cout << "sizeof(long long): " << sizeof(long long) << endl;
        cout << "sizeof(float): " << sizeof(float) << endl;
        cout << "sizeof(double): " << sizeof(double) << endl;
        cout << "sizeof(long double): " << sizeof(long double) << endl;
    }
}