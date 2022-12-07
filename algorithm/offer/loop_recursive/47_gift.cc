#include <iostream>

int GetMaxGiftValue(const int *value, int rows, int cols) {
  if (nullptr == value ||
	  rows <= 0 ||
	  cols <= 0) {
    return 0;
  }

  int **max_values = new int*[rows];
  for (int i = 0; i < rows; ++i) {
    max_values[i] = new int[cols];
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
	  int up = 0;
	  int left = 0; 

	  if (j > 0)
	    up = max_values[i][j-1];

	  if (i > 0)
	    left = max_values[i-1][j];

	  max_values[i][j] = std::max(up, left) + value[i*cols+j];
	}
  }

  int max_value = max_values[rows-1][cols-1];

  for (int i = 0; i <rows; ++i) {
    delete[] max_values[i];
  }
  delete[] max_values;

  return max_value;
} 


int GetMaxGiftValue2(const int *values, int rows, int cols) {
  if (nullptr == values ||
	  rows <= 0 ||
	  cols <= 0) {
    return 0;
  }

  int *max_values = new int[cols];
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
	  int up = 0;
	  int left = 0;

	  if (i > 0) // 这个逻辑判断仍然需要，只是将二维数组降为一维数组
	    up = max_values[j];

	  if (j > 0)
	    left = max_values[j-1];

	  max_values[j] = std::max(up, left) + values[i*rows+j];
	}
  }

  int max_value = max_values[cols-1];

  delete[] max_values;

  return max_value;
}


int main() {
  int test1[4] = {1,2,3,4};
  int test2[4] = {3, 4,5,6};
//  int test3[3][3] = {{5}, {7}, {9}};
  int *test4 = nullptr;

  std::cout << GetMaxGiftValue2(test1, 2, 2) << std::endl;
  std::cout << GetMaxGiftValue2(test2, 1, 4) << std::endl;
//  std::cout << GetMaxGiftValue2(test3, 3, 2) << std::endl;
  std::cout << GetMaxGiftValue(test4, 2, 2) << std::endl;

}
