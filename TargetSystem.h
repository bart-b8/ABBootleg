#ifndef TARGETSYSTEM_H
#define TARGETSYSTEM_H

#include <vector>

#include "Point.h"
#include "System.h"
#include "Engine.h"



class TargetSystem : public System {
 public:
  TargetSystem(Engine &engine);

  void Update();
 private:
  std::vector<Point> grid;
};

#endif
