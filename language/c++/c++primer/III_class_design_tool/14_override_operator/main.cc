#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <array>
#include <algorithm>
#include <iterator>
#include <functional>

using std::string;
using std::cout;
using std::cin;
using std::endl;

/*
class SalesData{
  friend std::ostream& operator<<(std::ostream&, const SalesData&);
  friend std::istream& operator>>(std::istream&, SalesData&);
};

std::ostream& operator<<(std::ostream& os, const SalesData& data) {
  const char* sep = ' ';
  os << data.isbn() << sep << data.units_dols << sep << data.revenue << sep << data.avr_price();
  return os;
}
*/

class ReadString {
 public:
  ReadString(std::istream& is = cin) : is(cin) {}
  std::string operator()() {
    std::string line;
	if (!getline(is, line))
	  line = "";
	return line;
  }
 private:
  std::istream &is;
};

void TestReadString() {
  ReadString read_string;
  std::vector<std::string> lines;
  while (true) {
    std::string line = read_string();
	if (!line.empty())
	  lines.emplace_back(line);
	else
      break;
  }
}

std::array<int, 10> StatWordsCount(std::istream& is) {
  std::array<int, 10> iarr;
  //std::fill(iarr.begin(), iarr.end(), 0);
  std::fill_n(iarr.begin(), 10, 0);
  std::string word;
  while (is >> word) {
    auto count = word.size();
	if (0 < count && count < 11) {
	  iarr.at(count) += iarr.at(count) + 1;
	}
  }
  return iarr;
}

void Test1442() {
  std::vector<std::string> svec = {"pooh", "pooh", "hello", "world"};
  auto it = std::find_if(svec.cbegin(), svec.cend(), std::bind(std::not_equal_to<std::string>(), std::placeholders::_1, "pool"));
  std::cout << "the first not pool is: " << *it << std::endl;
  std::vector<int> ivec = {1,2,3,4,5,6};
  std::transform(ivec.begin(), ivec.end(), ivec.begin(), std::bind(std::multiplies<int>(), std::placeholders::_1, 2));
  std::copy(ivec.begin(), ivec.end(), std::ostream_iterator<int>(std::cout, " "));
}

class Generator{
 public:
  Generator() { a= 0; }
  int operator()() {  		  
    a = a+5; 
	return a;
  }
 private:
  int a;
};

void Test1444() {
  std::map<std::string, std::function<int(int, int)>> binops = {
    {"+", std::plus<int>()},
	{"-", std::minus<int>()},
	{"*", std::multiplies<int>()},
	{"/", std::divides<int>()},
	{"%", std::modulus<int>()}
  };
	
  std::cout << __func__ << ": input left-operate-object, operator and right-operator-object"<< std::endl;
  int a, b;
  std::string op;
  std::cin >> a >> op >> b;

  std::cout << a << " " << op << " " << b << " = " << binops[op](a, b) << std::endl; 

}

void Test1443() {
  std::cout << std::endl <<  __func__ << ": ";
  int a = 100;
  Generator g;
  std::vector<int> ivec(10);
  std::generate(ivec.begin(), ivec.end(), g);
  std::copy(ivec.cbegin(), ivec.cend(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
  auto count = std::count_if(ivec.cbegin(), ivec.cend(), std::bind(std::modulus<int>(), a, std::placeholders::_1));
  std::cout << "count is " << count << std::endl;
}

class SmallInt{
 public:
  SmallInt(int i = 0) : val_(i) {
    if (i < 0 || i > 255)
	  throw std::out_of_range("Bad smallInt value");
  }

  explicit operator int() const {
    return val_;
  }

 private:
  std::size_t val_;
};

class Date{
 public:
  explicit operator bool() const {
    std::vector<std::vector<int>> days_per_month = {
	  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	};

	return 1 <= month_ && month_ <= 12 && 1 <= day && day <= days_per_month[IsLeapYear() ? 1 : 0][month_-1];
  }

  bool IsLeapYear(void) {
    return (year % 4 == 0 && year % 100 != 0) || 
		   (year % 400 == 0);
  }
 
 private:
  int years_;
  int month_;
  int day_;
};

int main(int argc, char* argv[]) {
  /*
  string s = "world";
  string u = "hi" + s;
  cout << u << endl;
		
  std::array<int, 10>&& iarr = StatWordsCount(std::cin);
  int index = 1;
  for (auto i : iarr) {
	std::cout << index++ << ": " << i << std::endl;
  }

  std::vector<int> ivec = {1,2,3,3,3,3,4,5,5,5,4,4,3,2,4,8,8};
  std::vector<int> ivec2;
  std::unique_copy(ivec.cbegin(), ivec.cend(), std::back_inserter(ivec2));
  for (auto i : ivec2)
	std::cout << i << " ";
  std::cout << std::endl;
*/

  Test1442();
  Test1443();
  Test1444();


  SmallInt si;
  si = 4;
  si + 3;

  return 0;
}
