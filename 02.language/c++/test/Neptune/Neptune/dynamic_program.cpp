#include "dynamic_program.h"
#include <algorithm>
#include <iostream>

namespace npt
{
	void DynamicProgram::runSamples()
	{
		std::cout << dropEggStep(2, 100);
	}

	int DynamicProgram::dropEggStep(int egg, int num)
	{
		if (egg < 1 || num < 1) return 0;

		//代表egg个鸡蛋，从num楼层冷下来所需的最小的次数
		//int (*f)[num + 1] = new int[egg + 1][num + 1];

		int** f = new int* [egg + 1];
		for (int i = 0; i < egg + 1; ++i)
			f[i] = new int[num + 1];

		for (int i = 0; i <= egg; i++) {
			for (int j = 1; j <= num; j++)
				f[i][j] = j; //初始化，最坏的步数
		}

		for (int n = 2; n <= egg; n++) {
			for (int m = 1; m <= num; m++) {
				for (int k = 1; k < m; k++) {
					f[n][m] = std::min(f[n][m], 1 + std::max(f[n - 1][k - 1], f[n][m - k]));
				}
			}
		}

		return f[egg][num];
	}

}
