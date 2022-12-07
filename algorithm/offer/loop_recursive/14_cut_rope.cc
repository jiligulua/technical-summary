#include <iostream>

using namespace std;

int getMaxMultiplyByCutRope(int length) {
  if (length < 2)
	return 0;
  else if (length == 2)
	return 1;
  else if (length == 3)
	return 2;
		
  int *f = new int[length+1];
  for (int i = 0; i < length+1; ++i)
    f[i] = 0;

  f[1] = 1; // 此时进行了切分
  f[2] = 2;
  f[3] = 3;
  
  // f[4] 可借用f[1]~f[3]完成
  int max = 0;
  for (int i = 4; i <= length; ++i) {
    max = 0; // 每一个长度，max都应该清空为0
	for (int j = 1; j <= i/2; ++j) {
	  int result = f[j] * f[i-j];
	  if (max < result) 
		max = result;
	}

	f[i] = max;
  }
    
  max = f[length];

  delete[] f;
  
  return max;
}


int main() {
  cout << "Input rope lenght:";
  int length;
  cin >> length;

  int result = getMaxMultiplyByCutRope(length);

  cout << "\nThe max result of cutting rop is " << result << endl;

  return 1;
}
