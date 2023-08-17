#ifndef CONTEXT_H
#define CONTEXT_H

#include <filesystem>

class Context {
 public:
  std::filesystem::path pth_level;
  bool screenchange = true;
  int exit_game = 0;
};

#endif
