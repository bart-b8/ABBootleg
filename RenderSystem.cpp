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
      cfg["game.playground_height"] - cfg["missiles.dst_height"] - classic.y_;
  return out;
}
void RenderSystem::DrawEntitys() {
  std::set<Entity *> wthTagSprite =
      engine_.GetEntityStream().WithTag(Component::Sprite);
  std::map<std::string, double> cfg = Config::Get().Map();
  // TODO(BD): Figure out how the coordinates work.
  for (Entity *entity : wthTagSprite) {
    Sprite sprite = dynamic_cast<Sprite_Component *>(
                        entity->GetComponent(Component::Sprite))
                        ->sprite;
    Point pos_al = convert_to_Allegro_Coordinate_System(
        (dynamic_cast<PositionComponent *>(
             entity->GetComponent(Component::Position)))
            ->pos);
    float dx = pos_al.x_;
    float dy = pos_al.y_;
    ak_->DrawScaledBitmap(sprite, static_cast<float>(0), static_cast<float>(0),
                          cfg["missiles.src_width"], cfg["missiles.src_height"],
                          dx, dy, cfg["missiles.dst_width"],
                          cfg["missiles.dst_height"]);
  }
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
