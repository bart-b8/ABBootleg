#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>
class HighScore {
 public:
  HighScore(std::string highscore_file_dir, int score, std::string level_file_dir = ""): highscore_file_dir(highscore_file_dir), level_file_dir(level_file_dir), score(score) {};
  std::string highscore_file_dir;
  std::string level_file_dir;
  int score;

  bool operator<(const HighScore &r) const {
    return this->score < r.score;
  }

  bool operator>(const HighScore &r) const {
    return this->score > r.score;
  }

  bool operator==(const HighScore& r) const {
    return this->score == r.score;
  }

  bool operator!=(const HighScore& r) const {
    return this->score != r.score;
  }

  bool operator>=(const HighScore& r) const {
    return this->score >= r.score;
  }

  bool operator<=(const HighScore& r) const {
    return this->score <= r.score;
  }

  bool cmp(const HighScore& a, const HighScore& b) {
    return a<b;
  }
};
#endif  // !HIGHSCORE_H
