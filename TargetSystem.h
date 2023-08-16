#ifndef TARGETSYSTEM_H
#define TARGETSYSTEM_H

#include <vector>

#include "Point.h"
#include "System.h"

class TargetSystem : public System {
 public:
  TargetSystem(Engine &engine): System(engine) {}

  void Update();
};

#endif
