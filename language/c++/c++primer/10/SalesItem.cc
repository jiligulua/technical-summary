#include "SalesItem.h"

SalesItem::SalesItem() 
    : revenue_(0.0) 
	, units_sold_(0) 
{}

SalesItem::SalesItem(std::istream& is) {
  is >> isbn_ >> units_sold_ >> revenue_; 
  if (!is) 
	*this = SalesItem();
}

SalesItem& SalesItem::operator+=(const SalesItem& sales_item) {
  units_sold_ += sales_item.units_sold_;
  revenue_ += sales_item.revenue_;
  return *this;
}

SalesItem& SalesItem::operator=(const SalesItem& sales_item) {
  units_sold_ = sales_item.units_sold_;
  revenue_ = sales_item.revenue_;
  isbn_ = sales_item.isbn_;
  return *this;
}

std::istream& operator>>(std::istream& is, SalesItem& sales_item) {
  return is >> sales_item.isbn_ >> sales_item.units_sold_ >> sales_item.revenue_;
}

std::ostream& operator<<(std::ostream& os, const SalesItem& sales_item) {
  return os << sales_item.isbn_ << " " << sales_item.units_sold_ << " " <<sales_item.revenue_;
}

