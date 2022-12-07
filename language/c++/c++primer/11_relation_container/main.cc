#include <utility>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <sstream>
#include "common.h"

using std::string;
using std::vector;
using std::pair;
using std::cout;
using std::endl;
using std::map;


void TestPair() {
  Tips(__func__);
  vector<pair<string, int>> data;

  data.push_back(pair<string, int>("Chris", 1));
  data.push_back({"Wu", 2});
  data.push_back(std::make_pair("Chaojiang", 3));
  data.emplace_back("beibei", 4);

  for(const auto & item : data) 
    cout << item.first << " " << item.second << endl;
  
  cout << endl;
}

class TransferText {
 private:
  map<string, string> reg_;
 
 public:
  TransferText(std::ifstream& in) {
    if (!in)
	  throw std::invalid_argument("Invalid argument");
	
	string alias;
	string dest;
	string line;
	while (std::getline(in, line)) {
	  std::istringstream iss(line);
      while (iss >> alias >> dest)
	    reg_[alias] = dest;
	}
  }
  
  ~TransferText() { reg_.clear(); }

  inline void set_reg(const std::map<string, string> reg) { reg_ = reg;}
  
  void ReplaceToNewFile(std::ifstream& in, std::ofstream& output) {
    string line;
	while (std::getline(in, line)) {
	  std::istringstream iss(line);
	  std::ostringstream oss;
	  string word;
	  while (iss >> word) {
		if (reg_.find(word) == reg_.cend())
	      oss << word << " ";
	    else 
		  oss << reg_[word] << " ";
	  }
	  
	  output << oss.str() << endl;
	}
  }
};

void TestMap() {
  Tips(__func__);
  std::multimap<string, string> families = {{"Wu", "Wu Chaojiang"}, {"Wu", "Wu Bingze"}, {"Wu", "Zhang Yiwei"}, {"Zhang", "Zhang San"}, {"Zhang", "Zhang Lili"}};
  //auto iter = families.equal_range("Wu");
  

  families.erase("Wu");

  for (const auto& it : families)
  //for (auto it = iter.first; it != iter.second; ++it) {
    cout << it.first << " " << it.second << endl;
  //}

  auto pr = families.equal_range("xxxx");
  if (pr.first == pr.second) {
   // families.insert();
  }
}
int main() {
  TestPair();
  TestMap();

  std::ifstream reg("./reg.txt");
  TransferText tt(reg);
  std::ifstream in("./sentence.txt");
  std::ofstream output("./new_sentence.txt");
  tt.ReplaceToNewFile(in , output);
  reg.close();
  in.close();
  output.close();
}
