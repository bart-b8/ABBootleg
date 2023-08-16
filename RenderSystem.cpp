#include "RenderSystem.h"
#include "./Engine.h"
#include "./PositionComponent.h"
#include "./Sprite.h"
#include "./Sprite_Component.h"
#include "Component.h"

Point RenderSystem::convert_to_Allegro_Coordinate_System(const Point classic) {
  std::map<std::string, double> cfg = Config::Get().Map();
  Point out;
  out.x_ = classic.x_;
  out.y_ =
      cfg["game.playground_height"] - classic.y_;
  return out;
}
void RenderSystem::DrawEntitys() {
  std::set<Entity *> wthTagSprite =
      engine_.GetEntityStream().WithTag(Component::Sprite);
  std::map<std::string, double> cfg = Config::Get().Map();
  // TODO(BD): Figure out how the coordinates work.
  for (Entity *entity : wthTagSprite) {
    Sprite_Component *sprtComp = dynamic_cast<Sprite_Component *>(
        entity->GetComponent(Component::Sprite));
    Sprite sprite = sprtComp->sprite;
    float sw = sprtComp->src_width;
    float sh = sprtComp->src_height;
    float dw = sprtComp->dst_width;
    float dh = sprtComp->dst_height;
    Point pos_al = convert_to_Allegro_Coordinate_System(
        (dynamic_cast<PositionComponent *>(
             entity->GetComponent(Component::Position)))
            ->pos);
    float dx = pos_al.x_;
    float dy = pos_al.y_ - dh;
    // TODO(BD): improve convert_to_Allegro_Coordinate_System
    // Can we leave missiles.dst_height out of
    // convert_to_Allegro_Coordinate_System? Can we instead redefine the base
    // coordiantes using sx and sy parameters to DrawScaledBitmap?
    ak_->DrawScaledBitmap(sprite, static_cast<float>(0), static_cast<float>(0),
                          sw, sh, dx, dy, dw, dh);
  }

  // TODO(BD): Draw all string entities
  // TODO(BD): Draw all Line entities
  // TODO(BD): Draw all Poly entities
}

bool RenderSystem::InScreenWindow() {
  // TODO(BD): Implement InScreenWindow.
  return true;
}

void RenderSystem::DrawScores() {}

void RenderSystem::Update() {
  if (!InScreenWindow() || !engine_.GetContext().screenchange) {
    return;
  }
  ak_->ClearScreen();
  ak_->DrawScaledBitmap(
      SPRT_BACKGROUND, static_cast<float>(0), static_cast<float>(0),
      Config::Get().Map()["game.background_width"],
      Config::Get().Map()["game.background_height"], static_cast<float>(0),
      static_cast<float>(0), Config::Get().Map()["game.screen_width"],
      Config::Get().Map()["game.screen_height"]);
  DrawEntitys();
  DrawScores();
  engine_.GetContext().screenchange = false;
  ak_->DrawOnScreen(true);
}
