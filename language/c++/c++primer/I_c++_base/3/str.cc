#include <cctype>
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
	string v("Hello World! 123 I love you !");
	cout << v << endl;
	
	for (auto &i : v)
		if (std::ispunct(i))
			i = '\0';
	cout << v << endl;

	//for (decltype(v.size()) index = 0; index != v.size(); ++index)
	//	if(std::isalnum(v[index]))
	//		v[index] = 'X';

	//
	//decltype(v.size()) index2 = 0;
	//while(index2 != v.size()) {
	//	if (std::isalnum(v[index2]))
	//		v[index2] = 'X';
	//}
	//for (auto &i : v)
		//if (std::isalnum(i))
	//	if (std::isalnum(i))
	//		i = 'X';

	//cout << v << endl;
	//string word1, word2;
	//while(cin >> word1 >> word2)
	//	if (word1 > word2)
	//		cout << word1 << " > " << word2 << endl;
	//	else 
	//		cout << word1 << " <= " << word2 << endl;
	
	//string line;
	//while(getline(cin, line))
	//	cout << line << endl;	
	return 0;
}
