#include "TargetSystem.h"
#include <fstream>

TargetSystem::TargetSystem(Engine &engine) : System(engine) {
  // read and evaluate level file.
  std::fstream fs(engine_.GetContext().pth_level, std::fstream::in);
  if (!fs.is_open()) {
    engine_.GetContext().exit_game = -1;
    return;
  }

  bool corrupt = false;
  const std::string allowed = "TBS";
  int i = 0;
  while (!fs.eof()) {
    char s;
    fs >> s;
    if (allowed.find(s) == std::string::npos) {
      corrupt = true;
    }
    i++;
  }
  if ((i - 1) != (Config::Get().Map()["level.level_size"] * Config::Get().Map()["level.level_size"])) {
    corrupt = true;
  }

  if (corrupt) {
    engine_.GetContext().exit_game = -2;
    return;
  }

  // TODO(BD): create positions for grid
  Point base;

  // TODO(BD): generate target entities including positions and add to engine.
}

void TargetSystem::Update() {
  // TODO(BD): check if any missiles are close to any targets.

  // TODO(BD): if yes, hit detection
  // if yes, force perpendiculous to edge. Above certain treshold: second or
  // third target.
  //
  //
  // TODO(BD): flash red when hit then remove:
  // TODO(BD): Check if any targets are no longer supporter. they need to drop
  // down.
}
