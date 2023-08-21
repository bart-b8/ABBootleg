#ifndef LAUNCHERSYSTEM_H
#define LAUNCHERSYSTEM_H

#include <list>
#include <vector>

#include "Component.h"
#include "Entity.h"
#include "Point.h"
#include "System.h"
#include "./Sprite_Component.h"
#include "./PositionComponent.h"
#include "./Missile_CurrentComponent.h"
#include "./Sprite.h"
#include "./Engine.h"
#include "./Config.h"
#include "./Polygon_Component.h"

class LauncherSystem : public System {
 public:
  LauncherSystem(Engine &engine);

  ~LauncherSystem() {}  // Memeory management by Engine.

  void Update();

  void CreateQueue();

  void SetPosition(PositionComponent*, int);

  Component::Type select_type();

  void SetNewMissile(Entity *, int);

  void AddToQueue();

  bool MouseOnMissile();

 private:
  std::list<Entity *> queue;
  std::vector<Polygon_Component *> seat_poly_comps;
  std::vector<Point> ref_seat_Points;
};

#endif
