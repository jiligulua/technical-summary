#include "dp_fibonacci.h"
#include <iostream>

using namespace std;


namespace mars
{
    Fabonacci::Fabonacci() {}

    Fabonacci::~Fabonacci() {}

    void Fabonacci::run() {
        cout << "input n: ";
        cin >> n;

        calculate_(n);
    }

    int Fabonacci::calculate_(int i)
    {
        if (i == 0) {
            cout << 1 << " ";
            return 1;
        } 
        else if (i == 1) {
            cout << 1 << " ";
            return 1;
        } 
        else {
            int sum = calculate_(i-1) + calculate_(i-2);
            cout << sum << endl;
            return sum;
        }
    }
}