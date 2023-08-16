#include "LauncherSystem.h"
#include "./Component.h"
#include "./Missile_BlackComponent.h"
#include "./Missile_GreenComponent.h"
#include "./Missile_PurpleComponent.h"
#include "./Missile_YellowComponent.h"
#include "PositionComponent.h"
#include "Sprite.h"
#include "Sprite_Component.h"

LauncherSystem::LauncherSystem(Engine &engine) : System(engine) {
  // TODO(BD): When Constructing:
  // - add entities: lines (springs),
  // missile in catapult and
  // missiles in queue
  Entity *cat = new Entity;
  Sprite_Component *cat_sprite = new Sprite_Component;
  PositionComponent *loc = new PositionComponent;
  cat_sprite->sprite = SPRT_LAUNCHER;
  cat_sprite->dst_width = Config::Get().Map()["launcher.dst_width"];
  cat_sprite->dst_height = Config::Get().Map()["launcher.dst_height"];
  cat_sprite->src_width = Config::Get().Map()["launcher.src_width"];
  cat_sprite->src_height = Config::Get().Map()["launcher.src_height"];
  loc->pos.x_ = (Config::Get().Map()["missiles.missiles"] - 2) *
              (Config::Get().Map()["missiles.dst_width"] + 5);
  loc->pos.y_ = 0;
  cat->Add(cat_sprite);
  cat->Add(loc);
  engine_.AddEntity(cat);

  CreateQueue();
}

void LauncherSystem::Update() {
  if (ak_->IsMouseClicked() && MouseOnMissile()) {
    engine_.RemoveEntity(queue.front());
    engine_.GetContext().screenchange = true;
    AddToQueue();
  }
}

void LauncherSystem::SetPosition(PositionComponent *poscomp, int number) {
  if (number == 0) {
    poscomp->pos.y_ = Config::Get().Map()["missiles.current_y_offset"];
  } else {
    poscomp->pos.y_ = 0;
  }
  poscomp->pos.x_ = (Config::Get().Map()["missiles.dst_width"] + 5) *
                    (Config::Get().Map()["missiles.missiles"] - number - 1);
}

Component::Type LauncherSystem::select_type() {
  Component::Type type =
      Component::Type(rand() % int(Config::Get().Map()["missiles.missiles"]));
  return type;
}

void LauncherSystem::SetNewMissile(Entity *missile, int position) {
  Sprite_Component *spritecmp = new Sprite_Component;
  missile->Add(spritecmp);

  PositionComponent *poscomp = new PositionComponent;
  SetPosition(poscomp, position);
  missile->Add(poscomp);

  Component::Type type = select_type();
  if (type == Component::Yellow) {
    Component *missileComp = new Missile_YellowComponent;
    spritecmp->sprite = SPRT_MISSILE_1;
    missile->Add(missileComp);
  } else if (type == Component::Purple) {
    Component *missileComp = new Missile_PurpleComponent;
    spritecmp->sprite = SPRT_MISSILE_2;
    missile->Add(missileComp);
  } else if (type == Component::Green) {
    Component *missileComp = new Missile_GreenComponent;
    spritecmp->sprite = SPRT_MISSILE_3;
    missile->Add(missileComp);
  } else if (type == Component::Black) {
    Component *missileComp = new Missile_BlackComponent;
    spritecmp->sprite = SPRT_MISSILE_4;
    missile->Add(missileComp);
  }
}

void LauncherSystem::CreateQueue() {
  while (queue.size() < Config::Get().Map()["missiles.missiles"]) {
    Entity *missile = new Entity;

    SetNewMissile(missile, queue.size());

    engine_.AddEntity(missile);
    queue.push_back(missile);
  }
}

void LauncherSystem::AddToQueue() {
  queue.pop_front();
  int i = 0;
  for (Entity * queued : queue) {
    Component* pos = queued->GetComponent(Component::Position);
    SetPosition(dynamic_cast<PositionComponent *>(pos), i++);
  }
  Entity *missile = new Entity;
  SetNewMissile(missile, 3);
  engine_.AddEntity(missile);
  queue.push_back(missile);
}

void LauncherSystem::MouseLocation() {}

bool LauncherSystem::MouseOnMissile() {
  Point mousePoint = convert_to_Classic_Coordinate_System(ak_->GetMouse());
  Point offset = Point(Config::Get().Map()["missiles.radius_x"], Config::Get().Map()["missiles.radius_y"]);
  Point missile = dynamic_cast<PositionComponent *>(queue.front()->GetComponent(Component::Position))->pos;
  missile = missile + offset;
  Component::Type missileType;
  for (Component::Tag tag : queue.front()->GetTags()) {
    if (tag == Component::Missile_Black) {
      missileType = queue.front()->GetComponent(Component::Missile_Black)->GetType();
    } else if (tag == Component::Missile_Green) {
      missileType = queue.front()->GetComponent(Component::Missile_Green)->GetType();
    } else if (tag == Component::Missile_Purple) {
      missileType = queue.front()->GetComponent(Component::Missile_Purple)->GetType();
    } else if (tag == Component::Missile_Yellow) {
      missileType = queue.front()->GetComponent(Component::Missile_Yellow)->GetType();
    }
  }
  switch (missileType) {
    case Component::Purple:
    case Component::Yellow:
    case Component::Black:
      if (mousePoint*missile < Config::Get().Map()["missiles.radius_x"]) {
        return true;
      } else { return false; }
      break;
    case Component::Green:
      // TODO(BD): use hitdetection to detect
      return true;
      break;
  }
  return true;
}
