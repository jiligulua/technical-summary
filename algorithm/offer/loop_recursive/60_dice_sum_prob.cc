#include "60_dice_sum_prob.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <exception>

using namespace std;

int g_maxValue = 6;

void PrintProbabilty(int number) {
  if (number < 1)
    return;

  int *pProb[2];
  pProb[0] = new int[g_maxValue * number + 1];
  pProb[1] = new int[g_maxValue * number + 1];
  for (int i = 0; i < g_maxValue * number + 1; ++i) {
    pProb[0][i] = 0;
    pProb[1][i] = 0;
  }

  int flag = 0;

  for (int i = 1; i <= g_maxValue; ++i)
    pProb[flag][i] = 1;

  for (int k = 2; k <= number; ++k) {
    for (int i = 0; i < k; ++i)
	  pProb[1-flag][i] = 0;

	for (int i = k; i <= g_maxValue*k; ++i) {
	  pProb[1-flag][i] = 0;
	  for (int j = 1; j<=i && j<=g_maxValue; ++j)
	    pProb[1-flag][i] += pProb[flag][i-j];
	}

	flag = 1 - flag;
  }

  double total = pow((double)g_maxValue, number);
  for (int i = number; i <= g_maxValue*number; ++i) {
    double ratio = (double)pProb[flag][i] / total;
	cout << i << ": " << setprecision(3) << ratio * 100 << "%" << endl; 
  }
}


void CalcDiceSumByLoop(unsigned dice_number) {
  try {
    if (-1 == dice_number)
	  throw runtime_error("input minus number");

	unsigned total = 6*dice_number;
	unsigned *sum_count = new unsigned[total+1];
    for (unsigned i = 0; i <= total; ++i)
	  sum_count[i] = 0;

	unsigned total_count = std::pow(6, dice_number);
	if (total_count == 0)
	  throw runtime_error("pow value is zero!");

	calcDiceSumByLoop(dice_number, sum_count);

	cout << "Dice number " << dice_number << " has below probability" << endl;
    for (unsigned i = 1 * dice_number; i <= 6*dice_number; ++i) {
	  auto ratio = static_cast<double>(sum_count[i]) / total_count * 100.0;	
	  cout << i << ":" << sum_count[i] << " " << setprecision(3) << ratio << "%" << endl;
    }
  } catch (const exception & e) {
    cout << "Exception " << e.what() << endl;
  } catch (...) {
    cout << "Exception." << endl;
  }
}

void calcDiceSumByLoop(unsigned dice_number, unsigned *sum_count) {
  for (unsigned i = 1; i <= 6; ++i)
    sum_count[i] = 1;

  for (unsigned i = 2; i <= dice_number; ++i) {
    unsigned base = (i-1)*6;
	unsigned pre_base = (i-2)*6;

	for (unsigned k = 1; k <= 6; ++k) {
	  for (auto m = k; m <= 6; ++m)
	    sum_count[base+k] += sum_count[pre_base+m];
	}
	
	for (unsigned j = 1; j < i; ++j) 
	  sum_count[j] = 0;

	for (auto j = base; j >= i; --j) {
	  for (auto k = 1; k <= 6; ++k) {
		if (j > k)
		  sum_count[j] += sum_count[j-k];
	  }
	}
  }
}

void CalcDiceSumProb(unsigned number) {
  unsigned total = 0;
  try {
    total = std::pow(6, number);
	if (0 == total)
	  throw runtime_error("error pow exception");

    unsigned len = 6*number - number + 1;
    unsigned *s = new unsigned[len];
	
    for (unsigned i = 0; i < len; ++i)
      s[i] = 0;
  
    calcSum(number, s);
  
    for (unsigned i = 0; i < len; ++i) {
      auto prob = static_cast<double>(s[i]) / total;
      cout << i + number << ":" << s[i] << " " << setprecision(3)<< prob * 100 << "%" << endl;
	}
  } catch (const exception &e) {
    cout << "\nException for " << e.what() << endl;
  } catch (...) {
  	cout << "\nException" << endl;
  }
} 

void calcSum(unsigned base, unsigned *s) {
  for (unsigned i = 1; i <= 6; ++i)
    calcSum(base, base, i, s);
}

void calcSum(unsigned base, unsigned cur, unsigned sum, unsigned *s ) {
  if (cur == 1)
    s[sum-base]++;
  else {
    for (unsigned i = 1; i <= 6; ++i)
	  calcSum(base, cur-1, sum+i, s);
  }
}
