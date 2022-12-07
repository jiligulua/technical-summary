#include "test_vector.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

TestVector::TestVector()
{}

TestVector::~TestVector()
{}

template<typename T>
void test_push_back(T eof)
{
    cout << "input info: " << endl;
    T word;
    vector<T> text;
    while(cin >> word && word != eof)
        text.push_back(word);

    cout << "result: " << endl;
    for(auto item : text)
        cout << item << " ";

    cout << endl;
}

template<typename T>
void cur_print(const vector<T> & data) {
    cout << "len: " << data.size() << " print: ";
    decltype(data.size()) count = data.size();
    for (decltype(data.size()) i = 0; i < count; i++)
    {
        cout << data[i] << " ";
    }
    cout << "#";
    cout << endl;    
}

template<typename T>
void iter_print(const vector<T> & data) {
    cout << "len: " << data.size() << " print: ";
    auto it = data.cbegin();
    while (it != data.cend())
        cout << *it++ << " ";

    cout << "#";
    cout << endl;    
}

void test_initialize()
{
    vector<int> v1;
    iter_print<int>(v1);

    vector<int> v2(10);
    iter_print<int>(v2);

    vector<int> v3(10, 42);
    iter_print<int>(v3);

    vector<int> v4{10};
    iter_print<int>(v4);
    
    vector<int> v5{10, 42};
    iter_print<int>(v5);

    vector<string> v6{10};
    iter_print<string>(v6);

    vector<string> v7{10, "hi"};
    iter_print<string>(v7);
}

void sum_intergal()
{
    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "data: ";
    for (auto item : data)
        cout << item << " ";
    cout << endl;

    decltype(data.size()) count = data.size();
    auto sum_neighbor = [=] {
        cout << "neighbor sum is: ";
        for (vector<int>::size_type i = 0; i < count - 1; i++)
            cout << data[i] + data[i+1] << " ";
        cout << endl;
    };
    sum_neighbor();

    auto sum_relative = [=] {
        cout << "relative sum is: ";
        vector<int>::size_type beg = 0, end = count - 1;
        while (beg < end) 
        {
            cout << data[beg] + data[end] << " ";
            ++beg;
            --end;
        }
        cout << endl;
    };
    sum_relative();
}

void sum_intergal_with_iter(int length)
{
    if (length <= 0)
        return;
    
    vector<int> data(length, 0);
    int i = 0;
    generate(data.begin(), data.end(), [&i]()->int{ return i++;});

    cout << "data: ";
    for (auto item : data)
        cout << item << " ";
    cout << endl;

    cout << "neighbor sum: ";
    auto it = data.cbegin();
    while (it != data.cend() && ((it + 1) != data.cend())) {
        cout << *it + *(it + 1) << " ";
        it += 1;
    }

    cout << endl;
    cout << "head tail sum: ";
    auto beg = data.cbegin();
    auto end = data.cend();
    decltype(end - beg) diff = end - beg;
    while (beg != end && (end - beg >= 2)) {
        cout << *(beg++)  + *(--end) << " ";
    }
    cout << endl;
}

class Sequence{
    public:
    int a;
    Sequence() { a= 0;}
    inline int operator()(){ a = a + 3; return a;}
};


void iter_change_item_double() 
{
    cout << "iter_change_item_double: \n";
    vector<int> data(10);
    // generate_n(data.begin(), 10, rand);
    // generate(data.begin(), data.end(), rand);
    // generate(data.begin(), data.end(), [&](int a)->int {});

    // 实现等差数列，差值为3
    // Sequence se;
    // generate(data.begin(), data.end(), se);

    // lambda
    int a = 0;
    generate(data.begin(), data.end(), [&a]()->int{ a = a + 3; return a;});

    iter_print(data);

    auto iter = data.begin();
    while(iter != data.end())
    {
        *iter = 2 * (*iter);
        iter++;
    }
        
    iter_print(data);


    iter = data.begin();
    auto mid = data.begin() + data.size() / 2;
    if (iter < mid) {
        cout << "process data previous mid part data \n";
    }
}

void bin_sought(int length, int target) {
    vector<int> data(length);
    int i = 0;
    generate(data.begin(), data.end(), [&i]() -> int { return i++;});

    auto beg = data.begin();
    auto end = data.end();
    auto mid = data.begin() + (end - beg) / 2;

    while (mid != end && *mid != target) {
        if (target < *mid) {
            end = mid;
        } else {
            beg = mid + 1;
        }

        mid = beg + (end - beg) /2;
    }

    if (mid == data.end())  
        cout << "can't find " << target << endl;
    else
        cout << "mid content is: " << *mid << endl;
}

void TestVector::Test()
{
    sum_intergal();

    vector<vector<int>> ivec;
    test_initialize();
    // test_push_back<string>("#");
    // test_push_back<int>('#');
    iter_change_item_double();
    bin_sought(2, 4);
    sum_intergal_with_iter(5);
}