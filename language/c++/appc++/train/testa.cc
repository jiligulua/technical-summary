#include "testa.h"

TestA::TestA(const string &) {
	cout << "TestA: lvalue" << endl;
}

TestA::TestA(string &&) {
	cout << "TestA: rvalue" << endl;
}
