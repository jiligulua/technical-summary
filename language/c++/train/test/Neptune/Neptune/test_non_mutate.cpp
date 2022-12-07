#include "test_non_mutate.h"
#include "non_mutate.h"
#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

void test_np_search_n()
{
	int count = 2;
	string number = "world";

	vector<string> numbers{ "Hello", "world", "world", "I", "love", "you", "world" };

	auto it = np_serach_n<decltype(numbers.cbegin()), decltype(count), decltype(number)>(
		numbers.cbegin(), numbers.cend(), count, number);


	if (it != numbers.cend())
	{
		cout << "Find " << count << " " << number << " index is: " << it - numbers.cbegin();
	}
	else
	{
		cout << "Can't find " << count << " " << number;
	}

}


void test_np_serach_n_predicat(int count /*= 2*/)
{
	//int number = 4;
	//vector<int> data{ 1, 3, 4, 5, 2, 1, 7, 8, 9 };
	std::string number("hellooo");
	vector<decltype(number)> data{ "hello", "world", "chris", "I", "love", "you" };


	std::function<bool(decltype(*data.cbegin()), decltype(number))>  Predicate;

	auto it = np_serach_n<decltype(data.cbegin()), decltype(count), decltype(number), decltype(Predicate)>(
		data.cbegin(),
		data.cend(),
		count,
		number,
		[](decltype(*data.cbegin()) a, decltype(number) b) -> bool {
			return b.length() - a.length() > 2;
		});

	if (it != data.cend())
	{
		cout << "Find " << count << " index is: " << it - data.cbegin();
	}
	else
	{
		cout << "Can't find! ";
	}
}