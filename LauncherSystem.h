#ifndef LAUNCHERSYSTEM_H
#define LAUNCHERSYSTEM_H

#include <list>

#include "Component.h"
#include "Entity.h"
#include "Point.h"
#include "System.h"
#include "./Sprite_Component.h"
#include "./PositionComponent.h"
#include "./Sprite.h"
#include "./Engine.h"
#include "./Config.h"

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

  void MouseLocation();

  bool MouseOnMissile();

 private:
  std::list<Entity *> queue;
};

#endif
