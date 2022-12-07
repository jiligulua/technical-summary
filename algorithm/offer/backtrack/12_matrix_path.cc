#include <iostream>
#include <string>
#include <cstring>

bool HasPathCore(char *matrix, int rows, int cols, int row, int col, char *str, int& index, bool *visited) {
  if (str[index] == '\0')
    return true;

  bool has_path = false;
  if (row < rows && col < cols && 
	  matrix[row*cols+col] == str[index] && 
	  !visited[row*cols+col]) {
    visited[row*cols+col] = true;
	++index;

	// 回溯法，最经典的思维就是在这里，一直递归，若是返回是false，说明以这个col和row位起点的位置是不合适的，恢复原样
	has_path = HasPathCore(matrix, rows, cols, row+1, col, str, index, visited) ||
               HasPathCore(matrix, rows, cols, row-1, col, str, index, visited) ||
               HasPathCore(matrix, rows, cols, row, col+1, str, index, visited) ||
               HasPathCore(matrix, rows, cols, row, col-1, str, index, visited);
	if (!has_path) {
	  --index;
	  visited[row*cols+col] = false;
	}
  }

  return has_path; // 若是false，则返回后，利用rows和cols寻找下一个起点。若是true，就此返回，表示已找到一条路径。
}

bool HasPath(char *matrix, int rows, int cols,  char *str) {
  if (nullptr == matrix || rows <= 0 || cols <= 0 || nullptr == str)
    return false;


  bool *visited = new bool[rows * cols];
  memset(visited, 0, rows*cols);

  int index = 0;

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
	  if (HasPathCore(matrix, rows, cols, i, j, str, index, visited))
	    return true;
	}
  }
  return false;
}

int main() {
  		
  return 1;
}
