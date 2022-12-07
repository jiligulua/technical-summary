#include "test_array.h"
#include <iostream>
#include <algorithm>

using namespace std;

string sa[10];
int ia[10];

void TestArray::test_define() {
    constexpr unsigned sz = 10;
    int arr[sz] = {10,192};

    int (*Parray)[10] = &arr; // 注意int[10]是签名式，而*表示指针，&表示引用。数组的签名式需要带有维度。
    int (&arrRef)[10] = arr; // 是int[10]的数组进行引用啦

    cout << "print Parray content: ";
    print_data(*Parray, 10);
    cout << "print arrRef content: ";
    print_data(arrRef, 10);

    string sa2[10];
    int ia2[10];
}

void TestArray::Test() 
{
    test_define();
}

void TestArray::print_data(int a[], int len)
{
    for (size_t i = 0; i < len; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    
}