#ifndef _HASH_SALES_DATA_H_
#define _HASH_SALES_DATA_H_

#include <functional>
#include "sales_data.h"

namespace std {

	template<>
	struct hash<SalesData>
	{
		typedef size_t size_type;
		typedef SalesData argument_type;
		size_t operator()(const SalesData &s) const;
	};

	size_t hash<SalesData>::operator()(const SalesData &s) const
	{
		return hash<string>()(s.bookNo) ^
			   hash<unsigned>()(s.units_sold) ^
			   hash<double>()(s.revenue);
	}
}

#endif 
