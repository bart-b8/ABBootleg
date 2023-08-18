#ifndef TARGETSYSTEM_H
#define TARGETSYSTEM_H

#include <vector>
#include <map>

#include "Point.h"
#include "System.h"
#include "Engine.h"



class TargetSystem : public System {
 public:
  TargetSystem(Engine &engine);

  void Update();
 private:
  std::vector<Point> grid;
  std::map<Entity *, int> collided_missiles;
  std::map<Entity *, int> hit_tgts;

  void AddToCollidedMissiles(Entity *);
  void AddToHitTargets(Entity *);
  bool IsIn(std::map<Entity *, int>, Entity*);
  void Update_collided_Missiles();
  void Update_hit_tgts();
};

#endif
