#include "quote.h"

namespace mars {

double print_total(std::ostream& os, const Quote& quote, std::size_t n) {
  double ret = quote.net_price(n);
  os << "ISBN: " << quote.bookno() << " # sold: " << n << " total due: " << ret << std::endl;
  return ret;
}

} // namespace mars
