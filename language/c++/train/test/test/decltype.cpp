#include <stdio.h>


const int func_cint(void) { return 0; } 

int main() {
	decltype(func_cint()) c2 = 0;

	return 1;

}
