#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;


// 用于在gdb调试时，方便输出。调用方法(gdb) call printMatrix(c,3,3) call printMatrix(b,3,3)
void printMatrix(int **matrix, int i, int j) {
  for (int n = 0; n <= i; ++n) {
    for (int m = 0; m <= j; ++m) {
	  cout << matrix[n][m] << " ";
	}
	cout << endl;
  }
  cout << endl;
}


// 根据二维数组的内容，可以很好的理解递归。递归就是一步一步走，只有一个出口。
void printLCSByBFlag(int **b, int *X, int i, int j) {
  if (i == 0 || j == 0)
    return;

  if (b[i][j] == 0) {
    cout << X[i] << " ";
	printLCSByBFlag(b, X, i-1, j-1);
  } else if (b[i][j] == 1) {
    printLCSByBFlag(b, X, i-1, j);
  } else {
    printLCSByBFlag(b, X, i, j-1);
  }
}

void printLCS(int **b, int *X, int *Y, int i, int j) {
  if (i == 0 || j == 0)
    return; // 其中一个序列长度为0，则LCS长度为0，无字符

  if (b[i][j] == X[i]) {
    cout << X[i] << " ";
	printLCS(b, X, Y, i-1, j-1);
  } else if (b[i][j] == X[i-1]) {
    printLCS(b, X, Y, i-1, j);
  } else {
    printLCS(b, X, Y, i, j-1);
  }
}

void LCSlength(int *X, int m, int *Y, int n, int **c, int **b) {
  for (int i = 1; i <= m; ++i)
    c[i][0] = 0; // j = 0, LCS长度为0

  for (int j = 1; j <= n; ++j)
    c[0][j] = 0; // i = 0, LCS长度为0

  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
	  if (X[i] == Y[j]) {
	    c[i][j] = c[i-1][j-1] + 1;
		//b[i][j] = X[i]; // 此时的X[i],Y[j]是LCS的一个元素
		b[i][j] = 0; // 此时的X[i],Y[j]是LCS的一个元素
		// Xi-1和Yj的一个LCS，Xi和Yj-1的一个LCS，两者中较长的就是X和Y的LCS
	  } else if (c[i-1][j] >= c[i][j-1]) {
	    c[i][j] = c[i-1][j];
		b[i][j] = 1; // 用于保存当前有效的相同的值
	  } else {
	    c[i][j] = c[i][j-1];
		// 改成这种形式，通过递归，可以轻松找到对应的0位置，而通过1或-1可以知道向上或向下
		b[i][j] = -1; // 存储中间值，有什么用？可于C一一对应，用于输出公共子序列
	  }
	}
  }
}

int main() {
  try {
	constexpr int X_LEN = 8;
	constexpr int Y_LEN = 7;
    int X[] = {-1, 1, 4, 7, 14, 13, 32, 26, 36}; // len 8
    int Y[] = {-1, 1, 2, 3, 32, 45, 36, 24}; // len 7
    //int X[] = {-1, 1, 4, 3};
    //int Y[] = {-1, 2, 1, 3};
	
    int **c = new int*[X_LEN+1];
    int **b = new int*[X_LEN+1];
    for (int i = 0; i < X_LEN+1; ++i) {
      c[i] = new int[Y_LEN+1];
      b[i] = new int[Y_LEN+1];
	}

    for (int i = 0; i < X_LEN+1; ++i) 
      for (int j = 0; j < Y_LEN+1; ++j) {
        c[i][j] = 0;
        b[i][j] = 0;
      }

    LCSlength(X, X_LEN, Y, Y_LEN, c, b);
    //printLCS(b, X, Y, X_LEN, Y_LEN); 

	// 在b中使用标记位，逆序输出最长公共子序列
	printLCSByBFlag(b, X, X_LEN, Y_LEN);

	
	cout << endl;
  } catch(const exception &e) {
    cout << "Exception: " << e.what() << endl;
  } catch(...) {
    cout << "Exception!" << endl;
  }
  return 1;
}
