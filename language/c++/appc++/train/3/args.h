#ifndef _ARGS_H_
#define _ARGS_H_

#include <algorithm>
#include <ctime>
#include <iostream>
#include <tuple>
using namespace std;


template<int...>
struct IndexSeq{};

template<int N, int... Indexes>
struct MakeIndexes : MakeIndexes<N-1, N-1, Indexes...> {};

template<int... Indexes>
struct MakeIndexes<0, Indexes...>
{
		typedef IndexSeq<Indexes...> type;
};


template<typename... T>
void f(T... args)
{
		cout << sizeof...(args) << endl;
}

template<std::size_t I = 0, typename Tuple>
typename std::enable_if<I == std::tuple_size<Tuple>::value>::type printtp(Tuple t) {}

template<std::size_t I = 0, typename Tuple>
typename std::enable_if<I < std::tuple_size<Tuple>::value>::type printtp(Tuple t) 
{
		cout << std::get<I>(t) << " ";
		printtp<I + 1>(t);
}

template<typename... Args> 
struct MySum;

template<typename First, typename... Rest>
struct MySum<First, Rest...> : std::integral_constant<int, MySum<First>::value + MySum<Rest...>::value> 
{};

template<typename Last>
struct MySum<Last> : std::integral_constant<int, sizeof(Last)>
{};

//-------------------------------------------------------------------------------
//template<typename First, typename... Rest>
//struct MySum<First, Rest...>
//{
//		enum { value = MySum<First>::value + MySum<Rest...>::value };
//};
//
//template<typename Last> 
//struct MySum<Last>
//{
//		enum { value = sizeof(Last) };
//};
//--------------------------------------------------------------------------------

//// 可变参数模板类
//template<typename First, typename... Rest>
//struct MySum
//{
//		enum { value = MySum<First>::value + MySum<Rest...>::value};
//};
//
//template<typename First, typename Last>
//struct MySum<First, Last>
//{
//		enum { value = sizeof(First) + sizeof(Last)};
//};

// -----------------------------------------------------------------------------
//void print()
//{
//		cout << "empty" << endl;
//}
//
//-------------------------------------------------------------------------------
//template<typename... Args>
//void print(Args... args)
//{
//		printtp(std::make_tuple(args...));
//		cout << endl;
//}
//

//------------------------------------------------------------------------------
template<typename T>
void print(T t)
{
		cout << t <<  endl;
		cout << "end of print" << endl;
}

template<typename T, typename T1, typename T2>
void print(T t, T1 t1, T2 t2)
{
		cout << t << " " << t1 << " " << t2 << endl;
}


template<typename T, typename... Args>
void print(T t, Args... args)
{
		cout << t << " ";
		print(args...);
}

//template<typename T, typename... Args>
//iostream & operator<< (iostream &out, )

#endif
