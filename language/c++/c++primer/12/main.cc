#include <iostream>
#include "str_blob.h"

using std::cout;
using std::endl;

int main() {
  
  StrBlob b1;
  cout << "b1.Size is " << b1.Size() << endl;
  {
    StrBlob b2 = {"a", "an", "the"};			
	b1 = b2;
  }		  

  cout << "b1.Size is " << b1.Size() << endl;

  return 0;
}
