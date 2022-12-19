#include <stdio.h>
#include "hello.h"

int main() {
  hello("World");
#ifdef TEST_DEBUG
  printf("DEBUG\n");
#endif
  return 0;
}
