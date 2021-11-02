#include "test_vector.h"
#include <iostream>
#include <vector>
#include <string>

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

void test_initialize()
{
    vector<int> v1;
    cur_print<int>(v1);

    vector<int> v2(10);
    cur_print<int>(v2);

    vector<int> v3(10, 42);
    cur_print<int>(v3);

    vector<int> v4{10};
    cur_print<int>(v4);
    
    vector<int> v5{10, 42};
    cur_print<int>(v5);

    vector<string> v6{10};
    cur_print<string>(v6);


    vector<string> v7{10, "hi"};
    cur_print<string>(v7);

}

void TestVector::Test()
{
    vector<vector<int>> ivec;
    test_initialize();
    
    // test_push_back<string>("#");
    // test_push_back<int>('#');
}