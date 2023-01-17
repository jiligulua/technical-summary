#include <asteroid/text_query.h>

#include <fstream>
#include <sstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>


namespace asteroid {


TextQuery::TextQuery(std::ifstream &is) 
    : line(new std::vector<string>) {
	std::string line;
	std::string word;
	while (std::getline(is, line)) {
		lines_->push_back(line);
		std::istringstream iss(line);
		while (iss >> word) {
      auto &numbers = word_nos_[word];
      if (!numbers)
        numbers.reset(new set<line_no>);
      numbers->insert(lines_->size()-1); // 从第0行开始计数
		}
	}
}

QueryResult TextQuery::query(const std::string& word) const {
  static std::shared_ptr<set<line_no>> nodata(new set<line_no>);
	
	auto loc = word_nos_.find(word);
	if (loc == word_nos_.end()) 
    return QueryResult(word, nodata, lines_);
  else
    return QueryResult(word, loc->second, lines_);
}

std::ostream& Print(std::ostream &os, const QueryResult& qr) {
	os << qr.word_ << " occurs" 
     << qr.numbers_->size() << (qr.numbers_->size() > 1 ? "times" : "time")
     << std::endl;
  for (auto num : *qr.numbers_)
    os << "( line " << num + 1 << " ) "
       << *(qr.lines_->begin()+num) << std::endl;
	return os;
}


} // namespace asteroid
