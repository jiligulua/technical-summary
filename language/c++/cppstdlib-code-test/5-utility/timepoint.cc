#include <iostream>
#include <ctime>
#include <string>

int main() {
  using namespace std;

  time_t t = time(nullptr);
  cout << "current time:" << t << endl;

  cout << "current calendar: " << ctime(&t) << endl;

  cout << "elapse CPU time: " << clock() << endl;

}
