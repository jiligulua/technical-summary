#ifndef MARS_BASKET_H_
#define MARS_BASKET_H_

#include <iostream>
#include <memory>
#include <set>

#include "quote.h"

namespace mars {

class Quote;
class Basket {
 public:
  void AddItem(const Quote&);
  void AddItem(Quote&&);
  double TotalReceipt(std::ostream& os) const;

 private:
  static bool Compare(const std::shared_ptr<Quote>& lhs,
				      const std::shared_ptr<Quote>& rhs) {
    return true;
	//return lhs->isbn() < rhs->isbn();
  }

  std::multiset<std::shared_ptr<Quote>, decltype(Compare)*> items_ { Compare };
};


} // namespace mars

#endif // MARS_BASKET_H_
