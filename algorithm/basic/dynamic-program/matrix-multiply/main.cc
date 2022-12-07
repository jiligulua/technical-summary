#include <iostream>
using namespace std;

const int MAX_VALUE = 2147483647;

// 怎么理解这个打印函数呢？
void printChain(int **s, int i, int j) {
  if (i == j) {
    cout << "A" << i; //i==j, 说明是一个矩阵，输出
  } else {
    // 递归的优雅，需要学会欣赏
    cout << "(";
	printChain(s, i, s[i][j]);
	printChain(s, s[i][j]+1, j);
	cout << ")";
  }
}

void PrintParenthesisForMatrixMultiply(int n, int p[]) {
  // 首先创将存放最小运算次数的二维矩阵，并初始化
  // 使用从下至上的解决方法，逐步构建最小运算次数
  // 最后输出1～n的最小次数以及对应的圆括号分隔方式
  int **m = new int*[n+1];
  for (int i = 0; i < n+1; ++i) {
    m[i] = new int[n+1];
	m[i][i] = 0;
  }

  int **s = new int*[n+1];
  for (int i = 0; i < n+1; ++i) {
    s[i] = new int[n+1];
	for (int j = 0; j < n+1; ++j) 
	  s[i][j] = 0;
  }
  
  for (int l = 2; l <= n; ++l) // l为要拆成的矩阵链的长度 
    for (int i = 1; i <= n-l+1; ++i) {// 通过具体例子理解
	  int j = i+l-1; // 具体例子理解，有长度和起点i就可算出j的位置
	  m[i][j] = MAX_VALUE;
	  int q = 0; 
	  for (int k = i; k <= j-1; ++k) { // 设计到k+1的情况，所有j-1
        // pi表示Ai的行数
		q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j]; 
	    if (q<m[i][j]) {
	      m[i][j] = q;
	      s[i][j] = k;
	    }
	  }
	}

  cout << "最小运算次数为：" <<  m[1][n] << endl;
  cout << "分隔的圆括号为：";
  printChain(s, 1, n);
  cout << endl;

  for (int i = 0; i <= n; ++i) {
    delete[] m[i];
    delete[] s[i];
  }

  delete[] m;
  delete[] s;
}


int main() {

  int n = 7;
  int p[] = {30, 35, 15, 5, 10, 20, 25, 10};
  PrintParenthesisForMatrixMultiply(n, p);

  return 1;

}
