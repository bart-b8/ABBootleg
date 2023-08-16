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
  LauncherSystem(Engine &engine): System(engine) {
    // TODO(BD): When Constructing:
    // - add entities: catapult, lines (springs),
    // missile in catapult and
    // missiles in queue
    Entity * cat = new Entity;
    Sprite_Component * cat_sprite = new Sprite_Component;
    PositionComponent * loc = new PositionComponent;
    cat_sprite->sprite = SPRT_LAUNCHER;
    cat_sprite->dst_width = Config::Get().Map()["launcher.dst_width"];
    cat_sprite->dst_height = Config::Get().Map()["launcher.dst_height"];
    cat_sprite->src_width = Config::Get().Map()["launcher.src_width"];
    cat_sprite->src_height = Config::Get().Map()["launcher.src_height"];
    loc->pos.x_ = 120;
    loc->pos.y_ = 0;
    cat->Add(cat_sprite);
    cat->Add(loc);
    engine_.AddEntity(cat);
  }

  ~LauncherSystem() {}  // Memeory management by Engine.

  void Update();

  void CreateQueue();

  void AddToQueue();

  void MouseLocation();

  bool MouseOnMissile();

 private:
  std::list<Component *> vec_queue;
};

#endif
