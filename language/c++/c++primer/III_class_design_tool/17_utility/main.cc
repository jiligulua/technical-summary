#include <algorithm>
#include <bitset>
using std::bitset;
#include <fstream>
using std::fstream;
#include <iomanip>
#include <iostream>
using std::cout; using std::endl;
#include <iomanip>
#include <regex>
using std::regex; using std::regex_replace;
#include <string>
using std::string;
#include <tuple>
using std::tuple;
#include <vector>
using std::vector;

namespace primer {

class SalesData {
	friend bool compareIsbn(const SalesData &lhs, const SalesData &rhs);

 public:
	SalesData() = default;
	SalesData(const string& book) {}
	SalesData(const SalesData &rhs) { ibsn_ = rhs.ibsn_; }
	SalesData& operator=(const SalesData &rhs) { 
		if (this == &rhs)
			return *this;
		
		SalesData tmp(rhs);
		ibsn_.clear();
		ibsn_ = tmp.ibsn_;
		return *this;
	}

	// 若有内存分配的资源，必须使用移动构造函数和移动赋值运算符
	SalesData(SalesData && rhs) noexcept {
		ibsn_ = rhs.ibsn_;
	}

	SalesData& operator=(SalesData &&rhs) noexcept {
		if (this == &rhs)
			return *this;

		ibsn_ = rhs.ibsn_;
		return *this;
	}

 private:
	string ibsn_;
};

bool compareIsbn(const SalesData &lhs, const SalesData &rhs) {
	return lhs.ibsn_ < rhs.ibsn_;
}

typedef tuple<vector<SalesData>::size_type,
				           vector<SalesData>::const_iterator,
									 vector<SalesData>::const_iterator> matches;
vector<matches>
FindBook(const vector<vector<SalesData>> &files,
				 const string &book) {
	vector<matches> ret;
		for (auto it = files.cbegin(); it != files.cend(); ++it) {
		auto found = std::equal_range(it->cbegin(), it->cend(), book, compareIsbn);
		if (found.first != found.second) 
			ret.push_back(std::make_tuple(it-files.cbegin(), found.first, found.second));
	}
	return ret;
}

typedef std::pair<vector<SalesData>::size_type,
				          std::pair<vector<SalesData>::const_iterator,
									          vector<SalesData>::const_iterator>> matches2;

vector<matches2>
FindBook2(const vector<vector<SalesData>> &files,
				 const string &book) {
	vector<matches2> ret;
		for (auto it = files.cbegin(); it != files.cend(); ++it) {
		auto found = std::equal_range(it->cbegin(), it->cend(), book, compareIsbn);
		if (found.first != found.second) 
			ret.push_back(std::make_pair(it-files.cbegin(), found));
	}
	return ret;
}

} // namespace mars

void test_1710() {
  std::cout << __func__ << std::endl;
  bitset<32> bv;
  bv.set(1);
  bv.set(2);

  bv.set(3);
  bv.set(5);
  bv.set(8);
  bv.set(13);
  bv.set(21);

  std::cout << bv << std::endl;
  
  std::size_t init = 1 | (1 << 2) | (1 << 3) | (1 << 5) | (1 << 8) | (1 << 13) | (1 << 21);
  bitset<32> bv1(init);
}

template <std::size_t N> 
class Exam {
 public:
  Exam() : solution_() {}

  void solution(std::size_t n, bool flag) { solution_.set(n, flag); }
  bitset<N> get_solution(void) { return solution_; }

  std::size_t Score(const bitset<N> &answer) {
    std::size_t score = 0;
    for (std::size_t i = 0; i < N && (solution_[i] == answer[i]); ++i) {
      ++score;
    }
    return score;
  }

 private:
  bitset<N> solution_;
};

void test_1732() {
  std::regex re("[[:alnum:]]*[^c]ei[[:alpha:]]*", std::regex::icase);
  std::string str("frieindeight neighboor");

  for (std::sregex_iterator it(str.begin(), str.end(), re), end_it;
       it != end_it; ++it) 
    std::cout << it->str() << std::endl;
}

void test_1714() {
  //std::regex re("[[:alnum:]]*\\.(cc|cpp|c)$");
  std::regex re("[[:alnum:]]*[^c]ei[[:alpha:]]");
  std::smatch result;
  std::string str("friend");

  if (std::regex_search(str, result, re)) {
    std::cout << result.str() << std::endl;
  } else {
    std::cout << "Not match" << std::endl;
  }
}

void TestRegexReplace() {
  cout << __func__ << endl;
  string format = "$2.$5.$7";
  string pattern = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
  regex r(pattern);
  string line;
  cout << "Please input the elephone number: " << endl;
  while (getline(std::cin, line)) {
    std::cout << regex_replace(line, r, format, std::regex_constants::format_no_copy);
  }
}

void TestIO() {
  std::cout << __func__ << endl;
  std::cout << std::boolalpha << true << " " << false << std::endl;  
  std::cout << std::noboolalpha;
  std::cout << "Hello World" << std::ends << "I love you" << endl;
  float f1 = 1233.1415926;
  std::cout << f1 << endl;
  std::cout << std::scientific << f1 << std::fixed << endl;
  float f2 = 0.002312453;
  //std::cout << std::hexfloat << f2 << std::defaultfloat <<  endl;
  std::cout << std::setprecision(7) << f2 <<  endl;
}

void TestManipulator() {
  cout << __func__ << endl;
  int i = -16;
  double d = 3.1415926;
  cout << "i: " << std::setw(12) << i << "|" << endl; 
  cout << "d: " << std::setw(12) << d << "|" << endl; 
  cout << std::left;
  cout << "i: " << std::setw(12) << i << "|" << endl; 
  cout << "d: " << std::setw(12) << d << "|" << endl; 
  cout << std::right;

  cout << "i: " << std::setw(12) << i << "|" << endl; 
  cout << "d: " << std::setw(12) << d << "|" << endl; 

  cout << std::internal;
  cout << "i: " << std::setw(12) << i << "|" << endl; 
  cout << "d: " << std::setw(12) << d << "|" << endl; 

  cout << std::setfill('#');
  cout << "i: " << std::setw(12) << i << "|" << endl; 
  cout << "d: " << std::setw(12) << d << "|" << endl; 
  //cout << "i: " << std::setw(12) << i << "|" << endl; 
  //cout << "d: " << std::setw(12) << d << "|" << endl; 
  //char ch;
  //while (std::cin.get(ch))
  //  std::cout.put(ch);

  //char sz[1024] = {0};
  //std::cin.getline(sz, 1024, '#');
  ////std::cin.get(sz, 1024, '#');
  //std::cout << sz ;

  //is.getline(sz, SIZE, ':');
  //cout << sz << endl;
  //is.read(sz, SIZE);
  //cout << sz << endl;
  //cout << is.gcount() << endl;
  //int ch;
  //while ((ch = std::cin.get()) != EOF)
  //  std::cout.put(ch);
  //cout << "end of test manipulate" << endl;
  
}

void TestIO2() {
  std::string path("/home/chris/technical-summary/language/c++/c++primer/III_class_design_tool/17_utility/17.txt");
  std::ifstream is(path, std::ios_base::in);
  constexpr unsigned SIZE = 10;
  char sz[SIZE] = {0};
  while (!is.eof()) {
    is.getline(sz, SIZE);
    cout << sz << endl;
    if (!is.good()) {
      if (is.gcount() == 9) 
        is.clear();
      else 
        break;
    } else {
      cout << endl;
    }
  }

  std::clog << "Hello, I am a log." << endl;
}

void AddPosInLastLine() {
  std::string path("/home/chris/technical-summary/language/c++/c++primer/III_class_design_tool/17_utility/17.txt");
  std::fstream inout(path, fstream::ate | fstream::in | fstream::out);
  if (!inout) {
    std::cerr << "Can't open the file" << std::endl;
    return;
  }

  auto end_mark = inout.tellg();
  inout.seekg(0, fstream::beg);
  string line;
  size_t cnt = 0;
  while (inout 
         && inout.tellg() != end_mark 
         && getline(inout, line)) {
    cnt += line.size() + 1;
    auto mark = inout.tellg();
    inout.seekg(0, fstream::end);
    inout << cnt;
    if (mark != end_mark) 
      inout << " ";
    inout.seekg(mark);
  }
  inout.seekp(0, fstream::end);
  inout << endl;
}

int main(int argc, char* argv[]) {
  bitset<13> bitvec(5);   // 101
  if (bitvec.any())
    std::cout << "has 1" << std::endl;
  else 
    std::cout << "has no 0" << std::endl;

  std::cout << bitvec.count() << std::endl;
  bitvec.set(1);
  std::cout << bitvec.count() << std::endl;
  std::cout << std::boolalpha << bitvec[0] << std::endl;
  std::cout << bitvec.to_ulong() << std::endl;
  std::cout << bitvec.to_string() << std::endl;
  std::cout << bitvec << std::endl;
  //std::cin >> bitvec;
  //std::cout << bitvec << std::endl;

  //bitset<14> bv;
  //std::cin >> bv;
  //std::cout << bv;
  
  std::cout << "sizeof(unsigned long)" << sizeof(unsigned long) << std::endl;
  std::cout << "sizeof(unsigned long long)" << sizeof(unsigned long long) << std::endl;

  test_1710();
  test_1714();
  test_1732();

  //TestRegexReplace();
  TestIO();
  TestManipulator();
  TestIO2();
  AddPosInLastLine();

  return 1;
}
