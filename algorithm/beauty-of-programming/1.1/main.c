#include<unistd.h>
int main() {
  long int mhz = 1000000;
  long int count = 21000 * mhz;

  for(;;) {
    for(long int i = 0; i < count; ++i)
	  ;
	usleep(10000);
  }
  return 1;
}
