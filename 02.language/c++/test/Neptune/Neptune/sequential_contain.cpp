#include "sequential_contain.h"
#include <sstream>


namespace npt
{
	ContainTest::ContainTest(void)
	{}

	void ContainTest::test(void)
	{
		list<deque<int>> ldData;

		list<int> li = { 1, 2, 3, 4, 5, 6, 7 };
		vector<double> vd(li.begin(), li.end());
		
		vector<int> vi = { 4, 5, 6, 7, 8, 9, 10 };
		vector<double> vd2(vi.begin(), vi.end());

		li = { 8,0 };

		list<int> il2 = { 1,2,3,4,5,6 };
		vector<int> iv2 = { 1,2,3,4,5,6,4,4,4 };
		int ret = compare<list<int>, vector<int>>(il2, iv2);

		Student st1("chris");
		Student st2("peter");
		list<Student> lstu = { st1, st2 };

		Student st3("juno");
		lstu.push_back(st3);
		lstu.emplace_back("Jupiter");

		//inputAndPrint<deque<string>>();
		//inputAndPrint<list<string>>();
		copyOddAndEven();
		testInsert();

		vector<int> vi3;
		//cout << vi3[0]; // 严重设计错误，编译器并不检查；而用at，编译器会检查错误
		try
		{
			cout << vi3.at(0);
		}
		catch (...) {}

		getFirstItem();
		testDelete();
		testForwardList();
		modifyLoop();
		modifyLoopWithList();
		modifyLoopWithForwardList();
		nonSaveEnd();
		test0934();
		test0939();
		test0941();
		otherString();
		test943_44(); 
		test945();
		test947();
		test949();
		test950();
		test951();
		testDeque();
		testAdapter();
	}


	template<typename U>
	void ContainTest::inputAndPrint()
	{
		string word;
		U dstr;
		while (cin >> word && word != "#")
		{
			dstr.push_back(word);
		}

		auto iter = dstr.cbegin();
		while (iter != dstr.cend())
			cout << *iter++ << " ";

		cout << std::endl;
	}

	void ContainTest::copyOddAndEven()
	{
		list<int> il = { 1,2,3,4,5,6,7,8,9 };
		deque<int> od, even;

		for (auto item : il)
		{
			if (item % 2 == 0)
				even.push_back(item);
			else
				od.push_back(item);
		}

	}

	void ContainTest::testInsert()
	{
		vector<int> iv = { 1,2,3,4,5,6,7,8,9 };
		vector<int>::iterator iter = iv.begin(),
			mid = iv.begin() + iv.size() / 2;

		int some_val = 2;
		while (iter != mid)
		{
			if (*iter++ == some_val)
			{ 
				iter = iv.insert(iter, 20 * some_val);
				mid = iv.begin() + iv.size() / 2;
			}
		}
	}

	void ContainTest::getFirstItem()
	{
		vector<int> vi = { 1,2,3,4,56 };
		cout << vi[0] << endl;
		cout << vi.at(0) << endl;
		cout << *vi.begin() << endl;
		cout << vi.front() << endl;


	}

	void ContainTest::testDelete()
	{
		list<int> il = { 1,2,3,4,5,6,7,8 };
		auto elem1 = il.begin();
		auto elem2 = il.begin();

		elem1 = il.erase(elem1, elem2);


		int ia[] = { 0,1,2,3,5,8,13,21,55,89 };
		list<int> li(ia, ia + sizeof(ia) / sizeof(int));
		auto iter = li.begin();
		while (iter != li.end())
		{
			if (*iter % 2 == 1)
				iter = li.erase(iter);
			else
				++iter;
		}

		vector<int> vi(ia, ia + sizeof(ia)/sizeof(int));
		auto iter2 = vi.begin();
		while (iter2 != vi.end())
		{
			if (*iter2 % 2 == 0)
				iter2 = vi.erase(iter2);
			else
				++iter2;
		}
	}

	void ContainTest::testForwardList()
	{
		forward_list<int> fi = {1,2,3,4,5,6,7,8};
		auto fb = fi.before_begin();
		auto fb2 = fi.insert_after(fb, 50);
		fi.insert_after(fb, 10, 100);
		fb2 = fi.insert_after(fb, { 12, 13, 14 });

		forward_list<int> f2;
		f2.emplace_after(f2.before_begin(), 1);

		auto fb3 = fi.erase_after(fi.begin());
	}

	void ContainTest::modifyLoop()
	{
		vector<int> vi = { 0,1,2,3,4,5,6,7,8,9 };
		auto iter = vi.begin();

		while (iter != vi.end()) 
		{
			if (*iter % 2)
			{
				//iter = vi.insert(iter, *iter++); // 当最后一个元素插入之后，再加+2，会发送越界问题。
				iter = vi.insert(iter, *iter);
				iter += 2;
			}
			else
			{
				iter = vi.erase(iter);
			}
		}
	}

	void ContainTest::modifyLoopWithList()
	{
		list<int> li = { 0,1,2,3,4,5,6,7,8,9 };
		auto iter = li.begin();

		while (iter != li.end())
		{
			if (*iter % 2)
			{
				iter = li.insert(iter, *iter);
				++iter;
				++iter;// iter += 2; 不能使用，因为list不是连续的存储容器，只能通过++获得下一个所指向的迭代器。
			}
			else
			{
				iter = li.erase(iter);
			}
		}

	}

	void ContainTest::modifyLoopWithForwardList()
	{
		forward_list<int> li = { 0,1,2,3,4,5,6,7,8,9 };
		auto iter = li.begin();
		auto prev = li.before_begin();

		while (iter != li.end())
		{
			if (*iter % 2)
			{
				iter = li.insert_after(prev, *iter);
				prev = ++iter;
				++iter;
			}
			else
			{
				iter = li.erase_after(prev);
			}
		}
	}

	void ContainTest::nonSaveEnd()
	{
		vector<int> vi = { 0,1,2,3,4,5,6,7,8,9 };
		auto iter = vi.begin();
		while (iter != vi.end())
		{
			++iter;
			iter = vi.insert(iter, 42); 
			//vi.insert(iter, 42);	// 此处去掉iter，会引发异常，读写权限冲突。
			++iter;

		}
	}

	void ContainTest::test0934()
	{
		// 在发现第一个奇数之后，在该奇数之前插入相同的值，一直循环插入。
		vector<int> vi = { 0,1,2,3,4,5,6,7,8,9 };
		auto iter = vi.begin();
		while (iter != vi.end())
		{
			if (*iter % 2)
			{
				iter = vi.insert(iter, *iter);
				++iter;
			}
			
			++iter;
		}
	}

	void ContainTest::test0939()
	{
		cout << "test 0939" << endl;
		//vector<int> vi;
		////vi.reserve(100);
		//for (int i = 0; i < 100; ++i )
		//{
		//	vi.push_back(i);
		//	cout << vi.size() << " " << vi.capacity() << endl;
		//}

		cout << "test string append" << endl;
		string str;
		str.reserve(100);
		cout << "size:" << str.size() << " capacity:" << str.capacity() << " length: " << str.length() << endl;
		for (int i = 0; i < 150; ++i)
		{
			str.append("a");
		}
		cout << "size:" << str.size() << " capacity:" << str.capacity() << " length: " << str.length() << endl;
		str.resize(10);

		cout << "size:" << str.size() << " capacity:" << str.capacity() << " length: " << str.length() << endl;
		str.shrink_to_fit();
		cout << "size:" << str.size() << " capacity:" << str.capacity() << " length: " << str.length() << endl;

		str.resize(50);
		cout << "size:" << str.size() << " capacity:" << str.capacity() << " length: " << str.length() << endl;
		str.append("b");

		auto test_capacity = [](int init_size) {
			vector<string> svec;
			svec.reserve(1000);
			for (int i = 0; i < init_size; ++i)
				svec.push_back("hello");

			//cout << "capacity - begin: " << svec.capacity() << endl;
			svec.resize(svec.size() + svec.size() / 2);
			cout << "capacity - end: " << svec.capacity() << endl;
		};

		test_capacity(256);
		test_capacity(512);
		test_capacity(1000);
		test_capacity(1048);
	}

	void ContainTest::test0941()
	{
		vector<char> vc = { 'H', 'e', 'l', 'l', 'o' };
		string str(vc.cbegin(), vc.cend());
	}

	void ContainTest::otherString()
	{
		const char* cp = "Stately, plump Buck";
		string s;
		s.assign(cp, 7);
		s.insert(s.size(), cp + 7);

		string s1 = "some string", s2 = "some other string";
		s1.insert(0, s2);

	}

	void ContainTest::test943_44()
	{
		auto test_replace_by_iter = [=](const string& str, const string& oldVal, const string& newVal) -> string  {
			string s = str;
			string::size_type index = 0;
			string::size_type old_size = oldVal.size();
			while (index != s.size() - old_size)
			{
				string cur = s.substr(index, old_size);
				if (cur == oldVal)
				{
					// 方法一
					//auto it = s.erase(s.begin() + index, s.begin() + index + old_size);
					//auto itnew = s.insert(it, newVal.begin(), newVal.end());
					//index = itnew - s.begin() + newVal.size();

					// 方法二
					s.replace(index, old_size, newVal);
					index += newVal.size();
					
				}
				else
				{
					++index;
				}
			}
			return s;
		};


		string s = "Hello World, tho I love you tho haaa";
		string rt = test_replace_by_iter(s, "tho", "though");
	}

	void ContainTest::test945()
	{
		auto appendName = [=](const string& name, const string& pre, const string& post) -> string {
			string new_name = name;
			new_name.append(post);
			new_name.insert(new_name.begin(), pre.begin(), pre.end());
			return new_name;
		};

		string chris = appendName("Chris", "Mr.", "Jr.");
		string peter = appendName("Peter", "Ms.", "III");

		auto appendName2 = [=](const string& name, const string& pre, const string& post) -> string {
			string new_name = name;
			new_name.insert(new_name.size(), post);
			new_name.insert(0, pre);
			return new_name;
		};

		string chris2 = appendName2("Chris", "Mr.", "Jr.");
		string peter2 = appendName2("Peter", "Ms.", "III");
	}

	void ContainTest::test947()
	{
		string str = "ab2c3d7R4E6";
		string digital = "0123456789";
		
		string num;
		string chars;

		string::size_type pos = 0;
		while ((pos = str.find_first_of(digital, pos)) != string::npos)
		{
			num.append(1, str[pos]);
			++pos;
		}

		pos = 0;
		while ((pos = str.find_first_not_of(digital, pos)) != string::npos)
		{
			chars.append(1, str[pos]);
			++pos;
		}

		cout << "source:" << str << endl;
		cout << "num:" << num << endl;
		cout << "chars:" << chars << endl;

		string numbers("0123456789"), name("r2d2");
		auto pos2 = numbers.find(name); // string::npos 
		int pos3 = pos2; // string::npos 


	}

	void ContainTest::test949()
	{
		string source = "Pfizer and BioNTech announced Tuesday that they're beginning a clinical trial for an Omicron-specific Covid-19 vaccine, and Moderna revealed Wednesday that it has entered Phase 2 of its own trial of a vaccine that targets the variant, which is by far the dominant one in the United States right now.\
			About 50 % of eligible Americans have received a booster shot, according to the US Centers for Disease Controland Prevention, but the Pfizerand Moderna news might raise questions regardless.For those who have yet to get inoculated, should they wait until there is an Omicron - specific vaccine ? What if someone has already had Covid - 19 during the Omicron surge, do they still need a booster ? And what does this mean for people who've already gotten a booster, or those who received the one-dose Johnson & Johnson vaccine and then subsequently got a dose of another kind ?";

		string cender("bdfghjklpqy");
		string comma(",.'%");

		stringstream ss(source);

		string word;
		string::size_type maxLen = 0;
		string target;
		while (ss >> word)
		{
			if (string::npos != word.find_first_of(comma))
				continue;

			if (string::npos == word.find_first_of(cender))
			{
				if (word.size() > maxLen)
				{
					cout << word << " ";
					target = word;
					maxLen = word.size();
				}
			}

		}
		cout << endl;

		if (!word.empty())
			cout << "The word " << target << " is the longest word and has no ascender or descender char" << endl;
		else
			cout << "No such word" << endl;


		int i = 42;
		string s = std::to_string(i);
		int i2 = std::stol(s);
	}

	void ContainTest::test950()
	{
		vector<string> svec = { "12", "42", "39", "42", "12" };
		int sum = 0;
		for (auto item : svec)
			sum += stoi(item);


		vector<string> svec2 = { "12.9", "42", "39", "42", "12" };
		float sum2 = 0;
		for (auto item : svec2)
			sum2 += stof(item);

	}

	void ContainTest::test951()
	{
		Calendar cl("January 1,1900");
		Calendar c2("1/1/1900");
		Calendar c3("Jan 1 1900");
	}

	void ContainTest::testDeque()
	{
		deque<char> idq;
		for (int i = 0; i < 100; ++i)
		{
			idq.push_back(0);
			cout << "deque size: " << idq.size();
		}
	}

	void ContainTest::testAdapter()
	{
		cout << endl << "testAdapter" << endl;
		priority_queue<char> ipq;
		for (char i = 'a'; i <= 'z'; ++i)
		{
			ipq.push(i);
		}

		while (!ipq.empty())
		{
			cout << ipq.top() << " ";
			ipq.pop();
		}
		
	}

	Calendar::Calendar(const std::string& str)
	{
		// "January 1,1900、1/1/1900, Jan 1 1900"
		string sperator(" ,/");

		string::size_type pos(0), pre(pos);
		string ret;
		auto sperateCalendar = [&]() -> string {
			pre = pos;
			
			if ((pos = str.find_first_of(sperator, pre)) != string::npos)
				ret = str.substr(pre, pos - pre);
			else
				ret = str.substr(pre);

			++pos;
			return ret;
		};

		//pos = str.find_first_of(sperator, pos);
		string year = sperateCalendar();
		string month = sperateCalendar();
		string date = sperateCalendar();
		
		cout << "year:" << year << ", month:" << month << ", date:" << date << endl;
	}

}