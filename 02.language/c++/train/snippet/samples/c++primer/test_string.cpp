//#include "../../include/c++primer/test_string.h"
#include "test_string.h"
#include <iostream>
#include <string>

using namespace std;

TestString::TestString() {}

TestString::~TestString() {}

void TestString::ChageChar() {
       string  s = "some string";
    for (decltype(s.size()) index = 0; 
        index != s.size() && !isspace(s[index]); ++index) 
        {
            s[index] = toupper(s[index]);
        }

    cout << s << endl;
}

void TestString::Input() {    
    string input;
    while (getline(cin, input)) 
    {
        cout << input << endl;
    }   
}

void TestString::Test() {
    Input();
    ChageChar();
}

int main() {
    TestString ts;
    ts.Test();
}