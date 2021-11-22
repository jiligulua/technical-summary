#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;


template<typename ForwardIter, typename Integer, typename T>
ForwardIter np_serach_n(
	ForwardIter first,
	ForwardIter last,
	Integer count,
	const T& value)
{
	if (count < 0)
		return first;


	first = find(first, last, value);
	while (first != last)
	{
		ForwardIter cur = first;

		cur++;
		int n = count - 1;

		while (cur != last && n != 0 && *cur == value)
		{
			cur++;
			n--;
		}

		if (n == 0)
			return first;
		else
			first = find(cur, last, value);
	}

	return last;
}

template<typename ForwardIter, typename Integer, typename T, typename BinaryPred>
ForwardIter np_serach_n(
	ForwardIter first,
	ForwardIter last,
	Integer count,
	const T& value,
	BinaryPred binary_pred)
{
	if (count < 0)
		return first;

	while (first != last && !binary_pred(*first, value))
		++first;

	while (first != last)
	{
		ForwardIter cur = first;
		++cur;

		Integer n = count - 1;

		while (cur != last && n != 0 && binary_pred(*cur, value)) {
			cur++;
			n--;
		}

		if (n == 0)
			return first;
		else
		{
			first = cur;
			while (first != last && !binary_pred(*first, value))
				++first;
		}
	}

	return last;
}