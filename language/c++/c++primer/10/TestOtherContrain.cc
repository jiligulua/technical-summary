#include <list>
#include <forward_list>
#include "common.h"

using std::list;
using std::forward_list;

void TestSplice() {
  Tips(__func__);
  list<int> il = {1,3,5,7,9,11,13,15};
  list<int> il2 = {2, 4, 6, 8, 10, 12, 14};
  list<int> ltemp(il);
  //ltemp.splice(ltemp.begin(), il2, il2.begin());
  ltemp.splice(ltemp.begin(), il2, il2.begin(), il2.end());
  Print(ltemp);
  Print(il2);

  forward_list<int> ifl = {1,3,5,7,9,11,13,15};
  forward_list<int> ifl2 = {2, 4, 6, 8, 10, 12, 14};
  forward_list<int> fltemp(ifl);
  fltemp.splice_after(fltemp.begin(), ifl2);
  //fltemp.splice_after(fltemp.begin(), ifl2, ifl2.begin());
  //fltemp.splice_after(fltemp.begin(), ifl2, ifl2.begin(), ifl2.end());
  Print(fltemp);
  Print(ifl2);
}

int main() {
  TestSplice();
  return 1;
}
