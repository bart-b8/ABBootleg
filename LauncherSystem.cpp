#include "LauncherSystem.h"
#include "./Component.h"
#include "./Missile_BlackComponent.h"
#include "./Missile_GreenComponent.h"
#include "./Missile_PurpleComponent.h"
#include "./Missile_YellowComponent.h"
#include "./Polygon_Component.h"
#include "PositionComponent.h"
#include "Sprite.h"
#include "Sprite_Component.h"
#include "TargetSystem.h"
#include <vector>

// Inertia for the launcher
#define I 10

LauncherSystem::LauncherSystem(Engine &engine) : System(engine) {
  // Create Catapult with springs and add to engine
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

  std::vector<Point> poly1;
  poly1.push_back(Point(loc->pos.x_ + 12, loc->pos.y_ + 153));
  Point pnt1 = Point((Config::Get().Map()["missiles.dst_width"] + 5) *
                             (Config::Get().Map()["missiles.missiles"] - 1) +
                         Config::Get().Map()["missiles.radius_x"],
                     Config::Get().Map()["missiles.current_y_offset"] +
                         Config::Get().Map()["missiles.dst_height"]);
  poly1.push_back(pnt1);
  ref_seat_Points.push_back(pnt1);
  Polygon_Component *poly1cmpnt = new Polygon_Component(poly1);
  seat_poly_comps.push_back(poly1cmpnt);
  Entity *poly1ent = new Entity;
  poly1ent->Add(poly1cmpnt);
  engine_.AddEntity(poly1ent);

  std::vector<Point> poly2;
  poly2.push_back(Point(loc->pos.x_ + 16, loc->pos.y_ + 133));
  Point pnt2 = Point((Config::Get().Map()["missiles.dst_width"] + 5) *
                             (Config::Get().Map()["missiles.missiles"] - 1) +
                         Config::Get().Map()["missiles.radius_x"],
                     Config::Get().Map()["missiles.current_y_offset"]);
  poly2.push_back(pnt2);
  ref_seat_Points.push_back(pnt2);
  Polygon_Component *poly2cmpnt = new Polygon_Component(poly2);
  seat_poly_comps.push_back(poly2cmpnt);
  Entity *poly2ent = new Entity;
  poly2ent->Add(poly2cmpnt);
  engine_.AddEntity(poly2ent);

  std::vector<Point> poly3;
  poly3.push_back(Point(loc->pos.x_ + 102, loc->pos.y_ + 125));
  Point pnt3 = Point((Config::Get().Map()["missiles.dst_width"] + 5) *
                             (Config::Get().Map()["missiles.missiles"] - 1) +
                         Config::Get().Map()["missiles.radius_x"],
                     Config::Get().Map()["missiles.current_y_offset"] +
                         Config::Get().Map()["missiles.dst_height"]);
  poly3.push_back(pnt3);
  ref_seat_Points.push_back(pnt3);
  Polygon_Component *poly3cmpnt = new Polygon_Component(poly3);
  seat_poly_comps.push_back(poly3cmpnt);
  Entity *poly3ent = new Entity;
  poly3ent->Add(poly3cmpnt);
  engine_.AddEntity(poly3ent);

  std::vector<Point> poly4;
  poly4.push_back(Point(loc->pos.x_ + 92, loc->pos.y_ + 108));
  Point pnt4 = Point((Config::Get().Map()["missiles.dst_width"] + 5) *
                             (Config::Get().Map()["missiles.missiles"] - 1) +
                         Config::Get().Map()["missiles.radius_x"],
                     Config::Get().Map()["missiles.current_y_offset"]);
  poly4.push_back(pnt4);
  ref_seat_Points.push_back(pnt4);
  Polygon_Component *poly4cmpnt = new Polygon_Component(poly4);
  seat_poly_comps.push_back(poly4cmpnt);
  Entity *poly4ent = new Entity;
  poly4ent->Add(poly4cmpnt);
  engine_.AddEntity(poly4ent);

  CreateQueue();
}

void LauncherSystem::Update() {
  static Point mouseRef;
  static Point missileRefPos;
  static bool ref = false;
  static bool releasing = false;
  bool released = false;
  static Point dp;

  if (ak_->IsMouseClicked() && MouseOnMissile()) {
    // Record reference mousePoint
    ref = true;
    mouseRef = convert_to_Classic_Coordinate_System(ak_->GetMouse());

    // Record reference position of missile loaded
    missileRefPos = dynamic_cast<PositionComponent *>(
                        queue.front()->GetComponent(Component::Position))
                        ->pos;
    ak_->LoadLaunchSound();
  }

  if (ref && ak_->HasMouseMoved()) {
    Point mouseCur = convert_to_Classic_Coordinate_System(ak_->GetMouse());
    Point diff = mouseCur - mouseRef;

    // Change position of missile loaded to missileRefPos + diff
    dynamic_cast<PositionComponent *>(
        queue.front()->GetComponent(Component::Position))
        ->pos = missileRefPos + diff;

    // Change position of seat_points;
    for (long unsigned int i = 0; i < seat_poly_comps.size(); i++) {
      seat_poly_comps[i]->body_.back() = ref_seat_Points[i] + diff;
    }

    engine_.GetContext().screenchange = true;

  }

  if (ref && ak_->IsMouseReleased()) {
    ref = false;
    releasing = true;
  }

  if (releasing) {
    ak_->PlayLaunchSound();
    engine_.GetContext().screenchange = true;
    Point p = dynamic_cast<PositionComponent *>(
                  queue.front()->GetComponent(Component::Position))
                  ->pos;
    Point diff = p - missileRefPos;
    Point ddp = diff;
    ddp.Scale(-(double)1 / (double)I);
    dp = dp + ddp;
    p = p + dp;
    dynamic_cast<PositionComponent *>(
        queue.front()->GetComponent(Component::Position))
        ->pos = p;

    for (long unsigned int i = 0; i < seat_poly_comps.size(); i++) {
      Point offset;
      switch (i) {
        case 0:
        case 2:
          offset = Point(17.5, 35);
          break;
        case 1:
        case 3:
          offset = Point(17.5, 0);
          break;
      }

      seat_poly_comps[i]->body_.back() = p + offset;
    }

    if (abs(dp.x_) > abs(diff.x_)) {
      releasing = false;
      released = true;
    }
  }
  if (released) {
    released = false;

    // Change position of seat_points back to rest;
    for (long unsigned int i = 0; i < seat_poly_comps.size(); i++) {
      seat_poly_comps[i]->body_.back() = ref_seat_Points[i];
    }

    Missile_CurrentComponent * miscurComp = new Missile_CurrentComponent;
    engine_.RemoveEntity(queue.front());
    miscurComp->vel = dp;
    dp.Scale(0);
    queue.front()->Add(miscurComp);
    engine_.AddEntity(queue.front());
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

// Used after missile is shot. to replentish queue
void LauncherSystem::AddToQueue() {
  queue.pop_front();
  int i = 0;
  for (Entity *queued : queue) {
    Component *pos = queued->GetComponent(Component::Position);
    SetPosition(dynamic_cast<PositionComponent *>(pos), i++);
  }
  Entity *missile = new Entity;
  SetNewMissile(missile, 3);
  engine_.AddEntity(missile);
  queue.push_back(missile);
}

bool LauncherSystem::MouseOnMissile() {
  Point mousePoint = convert_to_Classic_Coordinate_System(ak_->GetMouse());
  Point offset = Point(Config::Get().Map()["missiles.radius_x"],
                       Config::Get().Map()["missiles.radius_y"]);
  Point missile = dynamic_cast<PositionComponent *>(
                      queue.front()->GetComponent(Component::Position))
                      ->pos;
  missile = missile + offset;
  Component::Type missileType;
  for (Component::Tag tag : queue.front()->GetTags()) {
    if (tag == Component::Missile_Black) {
      missileType =
          queue.front()->GetComponent(Component::Missile_Black)->GetType();
    } else if (tag == Component::Missile_Green) {
      missileType =
          queue.front()->GetComponent(Component::Missile_Green)->GetType();
    } else if (tag == Component::Missile_Purple) {
      missileType =
          queue.front()->GetComponent(Component::Missile_Purple)->GetType();
    } else if (tag == Component::Missile_Yellow) {
      missileType =
          queue.front()->GetComponent(Component::Missile_Yellow)->GetType();
    }
  }
  switch (missileType) {
  case Component::Purple:
  case Component::Yellow:
  case Component::Black:
    if (mousePoint * missile < Config::Get().Map()["missiles.radius_x"]) {
      return true;
    } else {
      return false;
    }
    break;
  case Component::Green:
    std::vector<Point> coor_Polytriangle;
    std::vector<Point> coor_mouse;

    coor_Polytriangle.push_back(missile - offset);
    coor_Polytriangle.push_back(
        missile - offset + Point(Config::Get().Map()["missiles.dst_width"], 0));
    coor_Polytriangle.push_back(
        missile + Point(0, Config::Get().Map()["missiles.radius_y"]));
    coor_mouse.push_back(mousePoint);
    return CheckCollision(coor_Polytriangle, coor_mouse);
  }
  return false;
}
