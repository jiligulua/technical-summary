#include <bitset>
using std::bitset;

// 17.2
template <std::size_t N> 
class Exam {
 public:
  Exam() : solution_() {}

  void solution(std::size_t n, bool flag) { solution_.set(n, flag); }
  bitset<N> get_solution(void) { return solution_; }

  std::size_t Score(const bitset<N> &answer) {
    std::size_t score = 0;
    for (std::size_t i = 0; i < N && (solution_[i] == answer[i]); ++i) {
      ++score;
    }
    return score;
  }
 
 private:
  bitset<N> solution_;
};


