#include <iostream>
#include <iostream>
#include "60_dice_sum_prob.h"

int main() {
  using namespace std;

  unsigned number;

  cout << "Input dice number: ";
  cin >> number;
  
  cout << "\nCalc by loop from book:" << endl;
  PrintProbabilty(number);

  cout << "\nCalc by loop from mine:" << endl;
  CalcDiceSumByLoop(number);

  cout << "\nCalc by recursive:" << endl;
  CalcDiceSumProb(number);

  return 1;
}
