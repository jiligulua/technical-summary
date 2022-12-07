#include <iostream>
#include <cstring>

int GetNumSum(int number) {
  int sum = 0;
  while (number != 0) {
    sum += number % 10;
	number /= 10;
  }
  return sum;
}

bool Check(int threshold, int rows, int cols, int row, int col, bool *visited) {
  if (row >= 0 && col >= 0 && row < rows && col < cols && 
	  !visited[row*cols+col] && 
	  GetNumSum(row) + GetNumSum(col) <= threshold)
    return true;
  else 
	return false;
}

int MoveZoneCountCore(int threshold, int rows, int cols, int row, int col, bool *visited) {
  int count = 0;
  if (Check(threshold, rows, cols, row, col, visited)) {
	visited[row*cols+col] = true;
    count = 1 + MoveZoneCountCore(threshold, rows, cols, row+1, col, visited) +
			MoveZoneCountCore(threshold, rows, cols, row-1, col, visited) +
			MoveZoneCountCore(threshold, rows, cols, row, col+1, visited) +
			MoveZoneCountCore(threshold, rows, cols, row, col-1, visited);
  }
  return 0;
}

int MoveZoneCount(int threshold, int rows, int cols) {
  if (threshold < 0 || rows <= 0 || cols <= 0)
    return 0;

  bool *visited = new bool[rows * cols];
  memset(visited, 0, rows*cols);
 
  int count = MoveZoneCountCore(threshold, rows, cols, 0, 0, visited);

  delete[] visited;

  return count;
}

int main() {
  return 1;
}
