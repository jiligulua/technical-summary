#ifndef MARS_PRIMER_SALES_ITEM_
#define MARS_PRIMER_SALES_ITEM_
#include <string>
#include <iostream>

class SalesItem {
  public:
	SalesItem();
    SalesItem(std::istream& is);
	
	inline std::string isbn() const  { return isbn_; }

	SalesItem& operator+=(const SalesItem& sales_item);
	SalesItem& operator=(const SalesItem& sales_item);

	friend std::istream& operator>>(std::istream& is, SalesItem& sales_item);
	friend std::ostream& operator<<(std::ostream& is, const SalesItem& sales_item);

  private:
	std::string isbn_;
	unsigned units_sold_;
	double revenue_;
};

#endif// MARS_PRIMER_SALES_ITEM_
