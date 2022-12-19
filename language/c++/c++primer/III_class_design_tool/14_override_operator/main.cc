#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

class SalesData{
  friend std::ostream& operator<<(std::ostream&, const SalesData&);
  friend std::istream& operator>>(std::istream&, SalesData&);
};

std::ostream& operator<<(std::ostream& os, const SalesData& data) {
  const char* sep = ' ';
  os << data.isbn() << sep << data.units_dols << sep << data.revenue << sep << data.avr_price();
  return os;
}

int main(int argc, char* argv[]) {
  string s = "world";
  string u = "hi" + s;

  cout << u << endl;
		
  return 0;
}
