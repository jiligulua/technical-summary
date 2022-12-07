#ifndef __OFFER_DICE_SUM_PROB__
#define __OFFER_DICE_SUM_PROB__

void PrintProbabilty(int number);
void CalcDiceSumByLoop(unsigned dice_number); 
void calcDiceSumByLoop(unsigned dice_number, unsigned *sum_count); 
void CalcDiceSumProb(unsigned number); 
void calcSum(unsigned base, unsigned *s);
void calcSum(unsigned base, unsigned cur, unsigned sum, unsigned *s);

#endif
