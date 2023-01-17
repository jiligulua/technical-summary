#include "basket.h"
#include "quote.h"

#include <memory>
#include <utility>

#include "quote.h"

namespace mars {


void Basket::AddItem(const Quote& sale) {
  items_.insert(std::shared_ptr<Quote>(sale.Clone()));
}

void Basket::AddItem(Quote&& sale) {
  items_.insert(std::shared_ptr<Quote>(std::move(sale).Clone()));
}

double Basket::TotalReceipt(std::ostream& os) const {
  double sum = 0.0;
  for (auto iter = items_.cbegin();
	   iter != items_.cend();
	   iter =  items_.upper_bound(*iter)) {
    sum += print_total(os, **iter, items_.count(*iter));
  }
  return sum;
}

} // namespace mars
