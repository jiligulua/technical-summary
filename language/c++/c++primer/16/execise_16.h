#ifndef _EXECISE_16_H_
#define _EXECISE_16_H_

#include <iostream>
#include <memory>

using std::cout;
using std::endl;


// 16.4
template <typename T1, typename T2>
auto find_y(const T1 &v1, const T2 &v2) -> decltype(v1.begin())
{
	auto iter = v1.cbegin();
	while (iter != v1.cend()) {
		if (equal_to<T2>()(*iter, v2))
			break;	
		else
			++iter;
	}

	return iter;
}

// 16.5
template <typename T, unsigned N>
void print_y(const T (&p) [N])
{
	for(size_t i = 0; i != N; ++i)
		cout << p[i] << " ";
	cout <<endl;
}	

// 16.6
template <typename T, unsigned N>
const T * begin_y(const T (&p) [N])
{
	return p;
}

template <typename T, unsigned N>
const T * end_y(const T (&p) [N])
{
	return p + N;
}

// 16.19
template <typename T>
void PrintContainItem(const T& t, std::ostream &os) {
  using size_type = typename T::size_type;
  auto it = t.cbegin();
  for (size_type i = 0; i != t.size(); ++i) {
    os << *it++ << " ";
  }
  os << endl;
}

#endif
