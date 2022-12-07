#include <stdio.h>


void swap(char *psrc, int length)
{
		printf("The raw string is: %s\n", psrc);
		if (psrc == nullptr || length < 0) 
		{
				return;
		}

		int len = length - 1;
		for (int i = 0; i < len/2; ++i)
		{
				char temp = psrc[i];
				psrc[i] = psrc[len-1 -i];
				psrc[length-1 - i] = temp;
		}
		printf("The reverse string is: %s\n", psrc);
}

int main(void)
{

		char str[] = "Hello, World";
		swap(str, sizeof(str)/sizeof(char));
		return 0;
}
