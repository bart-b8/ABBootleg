#ifndef CONTEXT_H
#define CONTEXT_H

#include <chrono>
#include <filesystem>
#include <list>

#include "./HighScore.h"

class Context {
 public:
  std::filesystem::path pth_level;
  bool screenchange = true;
  int exit_game = 0;
  int highscore_achieved = 0;
  std::list<HighScore> highscores;
  std::chrono::system_clock::time_point starttime;
  int elapsed_time;
};

#endif
