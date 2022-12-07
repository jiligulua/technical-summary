#include <iostream>
#include <ratio>

int main() {
  using namespace std;
  typedef ratio<5, 3> FiveThirds;
  cout << FiveThirds::num << "/"  << FiveThirds::den << endl;

  typedef ratio<0> Zero;

  auto r1 = ratio_divide<FiveThirds, Zero>;

}
