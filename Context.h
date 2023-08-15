#ifndef CONTEXT_H
#define CONTEXT_H

#include <filesystem>

class Context {
 public:
  std::filesystem::path pth_level;
  bool screenchange = true;
};

#endif
