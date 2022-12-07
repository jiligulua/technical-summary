#ifndef SEDNA_SCREEN_H_
#define SEDNA_SCREEN_H_

#include <initializer_list>
#include <iostream>

using std::cout;
using std::endl;

template <unsigned W, unsigned H> class Screen;

template <unsigned W, unsigned H>
std::ostream& operator<<(std::ostream &os, const Screen<W, H> &screen) {
  return os << screen.weight_ << " " << screen.height_ << endl;
}

template <unsigned W, unsigned H>
std::istream& operator>>(std::istream &is, Screen<W, H> &screen) {
  is >> screen.weight_ >> screen.height_;
  return is;
}

template <unsigned W, unsigned H>
class Screen {
 public:
  friend std::ostream& operator<<<W, H>(std::ostream &os, const Screen<W, H> &screen);
  friend std::istream& operator>><W, H>(std::istream &os, Screen<W, H> &screen);

  Screen() {
   weight_ = W;
   height_ = H;
  }
 

 private:
  unsigned weight_;
  unsigned height_;
};

#endif // SEDNA_SCREEN_H_
