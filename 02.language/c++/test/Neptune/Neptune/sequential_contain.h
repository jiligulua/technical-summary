#pragma once
#include <list>
#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include <forward_list>


using namespace std;


namespace npt
{
	class Student
	{
	public:
		Student(const std::string& name) 
			: name_(name) {}

	private:
		std::string name_;
	};

	class ContainTest
	{
	public:
		ContainTest(void);
		void test(void);

	private:
		template<typename U, typename V>

		int compare(const U &l, const V &v);
		template<typename U>
		void inputAndPrint();
		void copyOddAndEven();
		void testInsert();
		void getFirstItem();
		void testDelete();
		void testForwardList();
		void modifyLoop();
		void modifyLoopWithList();
		void modifyLoopWithForwardList();
		void nonSaveEnd();
		void test0934();
		void test0939();
		void test0941();
		void otherString();
		void test943_44();
		void test945();
		void test947();


	};

	template<typename U, typename V>
	int npt::ContainTest::compare(const U& l, const V& v)
	{
		auto lb = l.begin();
		auto le = l.end();

		auto vb = v.begin();
		auto ve = v.end();

		while (lb != le && vb != ve)
		{
			if (*lb == *vb)
			{
				++lb;
				++vb;
				continue;
			}


			if (*lb > *vb)
				return 1;
			else
				return -1;
		}

		if (lb == le && vb == ve)
			return 0;
		else if (lb != le)
			return 1;
		else
			return -1;
	}

	

}