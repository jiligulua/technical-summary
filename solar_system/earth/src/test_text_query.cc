#include <earth/test_text_query.h>

#include <iostream>
using std::cout; using std::cin;
#include <string>

#include <asteroid/text_query.h>

namespace earth {

void RunQueries(std::ifstream &infile) {
	asteroid::TextQuery tq(infile);

	while (true) {
		std::cout << "Please input word to look for, or q to quit: ";
		std::string s;
		if (!(cin >> s) || s == "q")
			break;                          

		asteroid::Print(std::cout, tq.query(s)) << std::endl;
	}
}

} // namespace earth
