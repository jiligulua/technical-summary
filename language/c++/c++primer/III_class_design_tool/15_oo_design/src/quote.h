#ifndef MARS_OO_QUOTE_H_
#define MARS_OO_QUOTE_H_
#include <string>
#include <iostream>

class Quote {
 public:
  Quote() = default;
  Quote(const std::string& book, double sales_price) 
		: bookno_(book)
		, price_(sales_price) {}

  std::string bookno() const { return bookno_; }
  virtual double net_price(std::size_t n) const { return n * price_; }
  virtual void Debug() { std::cout << bookno_ << " " << price_ << std::endl; }
  virtual ~Quote() = default;

 private:
  std::string bookno_;

 protected:
  double price_ = 0.0;
};

class DiscQuote : public Quote {
 public:
  DiscQuote() = default;
  DiscQuote(const std::string& book, double sale_price, std::size_t qty, double disc)
		: Quote(book, sale_price)
		, min_qty_(qty)
		, discount_(disc) {}

  double net_price(std::size_t n) const = 0; 
  void Debug() override final { std::cout << bookno() << " " << min_qty_ << " " << discount_ << " " << price_ <<  std::endl; }
 
 protected: 
  std::size_t min_qty_ = 0; // 适合折扣政策的最低购买量
  double discount_ = 0.0; // 以小数表示的折扣额
};

class BulkQuote : public DiscQuote {
 public:
  using DiscQuote::DiscQuote;
  BulkQuote() = default;
  BulkQuote(const std::string& book, double sales_price, std::size_t qty, double disc)
		: DiscQuote(book, sales_price, qty, disc) {}

  double net_price(std::size_t n) const override {
    if (n > min_qty_) 
	  return n * price_ * (1 - discount_);
	else 
	  return n * price_;
  }
};


double print_total(std::ostream& os, const Quote& quote, std::size_t n) {
  double ret = quote.net_price(n);
  os << "ISBN: " << quote.bookno() << " # sold: " << n << " total due: " << ret << std::endl;
  return ret;
}



#endif // MARS_OO_QUOTE_H_
