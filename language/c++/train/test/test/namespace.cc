#include <iostream>

namespace mathlib {
  namespace matrixlib {
    class matrix {};
    matrix operator* (const matrix &lhs, const matrix &rhs) { std::cout << "operator*" << std::endl; }
  }
}

mathlib::matrixlib::matrix mathlib::matrixlib::operator*(const matrix &, const matrix &);

int main() {

}
