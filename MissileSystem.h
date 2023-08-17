#ifndef MISSILESYSTEM_H
#define MISSILESYSTEM_H

#include <vector>

#include "Point.h"
#include "System.h"
#include "./Engine.h"

#define G 1

class MissileSystem : public System {
 public:
  MissileSystem(Engine &engine): System(engine) {};

  void Update();

 private:
  bool missile_OutOfBounds(const Point);

};

#endif
