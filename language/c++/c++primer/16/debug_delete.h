#ifndef SEDNA_TEMPLATE_H_
#define SEDNA_TEMPLATE_H_

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;

namespace yh {

class DebugDelete {
 public:
  DebugDelete(std::ostream &s = std::cerr) : os_(s) {}

  template <typename T>
  void operator()(T *p) const {
    os_ << "Delete unique_ptr" << endl;
	delete p;
  } 

 private:
  std::ostream &os_;
};


#endif // SEDDA_TEMPLATE_H_

} // namespace yh
