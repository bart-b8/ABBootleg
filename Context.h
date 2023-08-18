#ifndef CONTEXT_H
#define CONTEXT_H

#include <filesystem>
#include <vector>

class Context {
 public:
  std::filesystem::path pth_level;
  bool screenchange = true;
  int exit_game = 0;
  int highscore_achieved = 0;
  std::vector<int> highscores;
};

#endif
