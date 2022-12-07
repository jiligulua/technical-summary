#include <iostream> // P324 about string
#include <fstream>
#include <stdexcept>
#include <string>
#include <exception>
#include "common.h"

using std::string;

void ReplaceStr(string s, const string& old_value, const string& new_value) {
  if (s.size() < old_value.size() || old_value.empty() || new_value.empty())
	return;

  auto it = s.begin();
  while (it < s.end()-old_value.size()+1) {
    if (*it != *old_value.begin()) {
	  ++it;
      continue;
	}

	auto it_tmp = it;
    auto it_old = old_value.begin();
	while (*it_tmp == *it_old && it_old != old_value.end() && it_tmp != s.end()) {
	  ++it_tmp;
	  ++it_old;
	}

	if (it_old == old_value.end()) {
	  it = s.erase(it, it_tmp);
	  it = s.insert(it, new_value.begin(), new_value.end());
	  it += new_value.size();
	  continue;
	} else {
	  ++it; 
	}
  }
  Print(s);
}

void ReplaceStrByIndex(string s, const string& old_value, const string& new_value) { 
  if (s.size() < old_value.size() || old_value.empty() || new_value.empty())
    return;

  for (string::size_type i = 0; i <= s.size()-old_value.size(); ++i) {
    if (s.at(i) != old_value.at(0)) 
	  continue;

	auto i_tmp = i;
	auto old_index = 0;
	while (old_index < old_value.size() && i_tmp < s.size() && s.at(i_tmp) == old_value.at(old_index)) {
	  ++i_tmp;
	  ++old_index;
	}
	if (old_index == old_value.size()) {
	  s.replace(i, old_value.size(), new_value);
      i += new_value.size()-1;
	} else {
	  continue;
	}
  }
  Print(s);
}

string MatchName(string name, const string & pre, const string & post) {
  name.insert(0, pre);
  name.append(post);
  return std::move(name);
}

string MatchNameByPos(string name, const string & pre, const string & post) {
  name.insert(0, pre);
  name.insert(name.size(), post);
  return std::move(name);
}

void FindEveryItemInclude(const string &str, const string &sets) {
  string::size_type pos = 0;
  while ((pos = str.find_first_of(sets, pos)) != string::npos) {
    std::cout << str.at(pos) << " ";
	++pos;
  }
  std::cout << std::endl;
}

void FindEveryItemExclude(const string &str, const string &sets) {
  string::size_type pos = 0;
  while ((pos = str.find_first_not_of(sets, pos)) != string::npos) {
    std::cout << str.at(pos) << " ";
	++pos;
  }
  std::cout << std::endl;
}

void FindLongestWordWithMid(std::ifstream &ifs) {
  string tails_alpha("bdfghjklpqyABCDEFGHIJKLMNOPQRSTUVWXYZ");  
  string word;
  string longest_word;
  while (ifs >> word) {
    if (string::npos == word.find_first_of(tails_alpha)) {
	  if (word.size() > longest_word.size()) {
	    longest_word.assign(word);
	  }
	}
  }
  std::cout << "The longest word is " << word << std::endl;
}

void TransferNumber() {
  double d = 1.453647456453423;
  float f = 3.4354345665768687;
  int i = 12343524;
  std::cout << std::to_string(d) << " "
		    << std::to_string(f) << " "
			<< std::to_string(i) << std::endl;
  string str("11");
  std::cout << stoi(str, 0, 10) << " "
            << stoi(str, 0, 2) << " "
            << stoi(str, 0, 8) << " "
            << stoi(str, 0, 16) << std::endl; 
}

class Calendar {
  private:
    unsigned year_, month_, day_;
  
  public:
    Calendar(const string& calendar) {
	  string exclude(" ,/");
	  string::size_type pre = 0;
	  string::size_type pos = 0;
	  string month;
	  string day;
	  string year;
	  if ((pos = calendar.find_first_of(exclude)) != string::npos) {
	    month = calendar.substr(pre, pos-pre);
		pre = pos+1;
	  } else {
	    throw std::invalid_argument("month exception");
	  }

	  if ((pos = calendar.find_first_of(exclude, pos+1)) != string::npos) {
	    day = calendar.substr(pre, pos-pre);
		day_ = stoi(day);
		pre = pos;
	  } else {
	    throw std::invalid_argument("day exception");
	  }
	  year = calendar.substr(pos+1);
	  try {
	    year_ = stoi(year);
	  } catch (const std::exception & e) {
	    std::cout << e.what() << std::endl;
	  }
	}

	unsigned year() const { return year_; }
	unsigned month() const { return month_; }
	unsigned day() const { return day_; }
  
  private:
	unsigned TransferMonth(const string & month) {
	  
	}
};

int main() {
  string s("tho are the apples, tho I like it tho");
  string old_value("tho");
  string new_value("through");
  ReplaceStr(s, old_value, new_value);
  ReplaceStrByIndex(std::move(s), std::move(old_value), std::move(new_value));

  string name = "Chris";
  string pre = "Mr.";
  string post = " III";
  std::cout << MatchName(name, pre, post) << std::endl;
  std::cout << MatchNameByPos(name, pre, post) << std::endl;

  string numbers("0123456789");
  string alpha("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
  string str("ab2c3d7R4E6");
  Print(str);
  FindEveryItemInclude(str, numbers);
  FindEveryItemInclude(str, alpha);

  FindEveryItemExclude(str, numbers);
  FindEveryItemExclude(str, alpha);

  std::ifstream ifs("./test_str.txt");
  FindLongestWordWithMid(ifs);
  ifs.close();

  TransferNumber();

  Calendar cal("January 1, 1900");
  Calendar cal2("1/1/1900");
  Calendar cal3("Jan 1 1900");
}
