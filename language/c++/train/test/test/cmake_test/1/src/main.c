#include "hello.h"
#include <stdio.h>

int main()
{
		hello("World");
#ifdef MY_TEST_DEBUG
		printf("Debug\n");
#endif 
		return 0;
}
