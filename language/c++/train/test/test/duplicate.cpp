#include <stdio.h>
#include <cstring>

bool duplicate(int* pnumber, int length, int* pdup )
{
		if (pnumber == nullptr || pdup == nullptr || length < 1)
		{
				return false;
		}

		for (int i = 0; i < length; ++i)
		{
				if (pnumber[i] < 0 || pnumber[i] > length)
				{
						return false;
				}
		}

		for (int i = 0; i < length; ++i)
		{
				if (i == pnumber[i]) 
				{
						continue;

				}

				int value = pnumber[i];
				if (pnumber[value] == value) 
				{
						*pdup = value;
						return true;
				}

				else 
				{
						pnumber[value] = pnumber[i];
						i--;
						continue;
				}
		}

		return false;
}
 

int main(void)
{
		int number[] = {2, 3, 1, 0, 2, 5, 3};
		int pdup = 0;
		 bool bFound = duplicate(number, sizeof(number)/sizeof(int), &pdup); 
		//bool bFound = duplicate(nullptr, sizeof(number)/sizeof(int), &pdup); 
		
		if (bFound)
		{
			printf("I find the duplicate number, it's %d\n", pdup);
		}
		else 
		{
			printf("I don't find any duplicate number.\n");
		}
		
}
