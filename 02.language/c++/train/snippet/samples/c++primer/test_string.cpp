// #include "../../include/c++primer/test_string.h"
#include "test_string.h"
#include <iostream>
#include <string>

using namespace std;

TestString::TestString() {}

TestString::~TestString() {}

void TestString::test() {
    test_input();
    test_change_char();
}

void TestString::test_change_char() {
       string  s = "some string";
    for (decltype(s.size()) index = 0; 
        index != s.size() && !isspace(s[index]); ++index) 
        {
            s[index] = toupper(s[index]);
        }

    cout << s << endl;
}

void TestString::test_input() {    
    string input;
    while (getline(cin, input)) 
    {
        cout << input << endl;
    }   
}

int main() {
    TestString ts;
    ts.test();
}