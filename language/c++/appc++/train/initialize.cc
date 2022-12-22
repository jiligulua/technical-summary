#include <iostream>

using namespace std;


struct B
{
	int x;
	int y;
	B(int i, int j) : x(i), y(j) {}
} b = {123, 321};


struct ST
{
	int x;
	double y;

	ST(int i, double j) : x(i), y(j) {}
private:
	int z;
};

struct Foo 
{
	ST st;
	int x;
	double y;
};

int main()
{
	cout << "b.x=" << b.x << " b.y=" << b.y << endl;

	Foo foo = { {1, 1.0}, 2, 3.0};

	cout << "Foo:" << foo.st.x << " " << foo.st.y << " " << foo.x << " " << foo.y << endl;
	return 0;
}
