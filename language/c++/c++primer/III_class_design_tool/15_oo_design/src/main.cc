#include <iostream>
#include "quote.h"

using std::cout;
using std::endl;


int main() {
  Quote q("C++20", 68);
  BulkQuote bulk_quote("C++17", 58.0, 5, 0.2);

  DiscQuote d;

  q.Debug();
  bulk_quote.Debug();

}
