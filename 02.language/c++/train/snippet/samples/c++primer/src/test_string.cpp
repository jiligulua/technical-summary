#include "base.h"
#include "test_string.h"
#include <iostream>
#include <string>

using namespace std;

TestString::TestString() {}

TestString::~TestString() {}

void TestString::Test()
{
    // Input();
    // ChageChar();
    Exercise();
}

void TestString::Input()
{
    string input;
    while (getline(cin, input))
    {
        cout << input << endl;
    }
}

void TestString::ChageChar()
{
    string s = "some string";
    for (decltype(s.size()) index = 0;
         index != s.size() && !isspace(s[index]); ++index)
    {
        s[index] = toupper(s[index]);
    }

    cout << s << endl;
}

void UseWhile()
{
    string s = "Hello, String!";
    cout << "raw: " << s << endl;

    decltype(s.size()) index = 0;
    while (index < s.size())
    {
        s[index] = 'X';
        index++;
    }

    cout << "result: " << s << endl;
}

void UseFor()
{
    string s = "Hello, String!";
    cout << "raw: " << s << endl;

    for (char &item : s)
        item = 'X';

    cout << "result: " << s << endl;
}

void UsePunct()
{
    string puct = "Hello, String!";

    for (auto &item : puct)
        item = ispunct(item) ? ' ' : item;

    cout << "result of del punct : " << puct << endl;
}

void TestString::Exercise()
{
    UseWhile();
    UseFor();
    UsePunct();
}