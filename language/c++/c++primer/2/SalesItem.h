#ifndef SALES_ITEM_H
#define SALES_ITEM_H

#include <iostream>
#include <string>

class SalesItem
{

friend std::istream& operator>>(std::istream &, SalesItem &);
friend std::ostream& operator<<(std::ostream &, const SalesItem &);

friend SalesItem operator+(const SalesItem &, const SalesItem &);

public:
	SalesItem() {}
	SalesItem(std::istream &is) { is >> *this;}


public:
	inline double avgPrice() const { return revenue / units_sold; }
	std::string isbn() const { return bookNo; }

	SalesItem& operator+=(const SalesItem &rhs);

private:
	std::string bookNo;
	unsigned units_sold  {0};
	double revenue {0.0};
};

SalesItem& SalesItem::operator+=(const SalesItem &rhs) 
{
	units_sold = rhs.units_sold;
	revenue = rhs.revenue;
	return *this;
}

std::istream& operator>>(std::istream &in, SalesItem &s)
{
	double price;
	in >> s.bookNo >> s.units_sold >> price;
	if (in) 
		s.revenue = s.units_sold * price;
	else
		s = SalesItem();

	return in;
}

std::ostream& operator<<(std::ostream &out, const SalesItem &s)
{
	out << s.bookNo << " " << s.units_sold << " " << s.revenue << " "
		<< s.avgPrice();
	return out;
}

SalesItem operator+(const SalesItem &lhs, const SalesItem &rhs)
{
	SalesItem si(lhs);
	si.revenue += rhs.revenue;
	si.units_sold = rhs.units_sold;
	return si;
}

#endif
