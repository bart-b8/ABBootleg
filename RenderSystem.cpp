#include "RenderSystem.h"
#include "./Engine.h"
#include "./PositionComponent.h"
#include "./Sprite.h"
#include "./Sprite_Component.h"
#include "Component.h"

void RenderSystem::DrawEntitys() {
  std::set<Entity *> wthTagSprite =
      engine_.GetEntityStream().WithTag(Component::Sprite);
  std::map<std::string, double> cfg = Config::Get().Map();
// TODO(BD): Figure out how the coordinates work.
  for (Entity *entity : wthTagSprite) {
    Sprite sprite = dynamic_cast<Sprite_Component *>(
                        entity->GetComponent(Component::Sprite))
                        ->sprite;
    float dx = (dynamic_cast<PositionComponent *>(
                    entity->GetComponent(Component::Position)))
                   ->pos.x_;
    float dy = (dynamic_cast<PositionComponent *>(
                    entity->GetComponent(Component::Position)))
                   ->pos.y_;
    ak_->DrawScaledBitmap(sprite, (float)0, (float)0, (float)0, (float)0, dx,
                          dy, cfg["missile.width"], cfg["missile.hight"]);
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
