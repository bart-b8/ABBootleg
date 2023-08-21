#include "RenderSystem.h"
#include "./Engine.h"
#include "./PositionComponent.h"
#include "./Sprite.h"
#include "./Sprite_Component.h"
#include "./Polygon_Component.h"
#include "Component.h"
#include "Text_Component.h"

void RenderSystem::DrawEntitys() {
  std::set<Entity *> wthTagSprite =
      engine_.GetEntityStream().WithTag(Component::Sprite);
  std::map<std::string, double> cfg = Config::Get().Map();
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
    ak_->DrawScaledBitmap(sprite, static_cast<float>(0), static_cast<float>(0),
                          sw, sh, dx, dy, dw, dh);
  }

  // TODO(BD): Draw all string entities
  std::set<Entity *> wthTagPolygon =
      engine_.GetEntityStream().WithTag(Component::Polygon);
  for (Entity *entity : wthTagPolygon) {
    Polygon_Component * polycomp = dynamic_cast<Polygon_Component *>(
        entity->GetComponent(Component::Polygon));
    std::vector<Point> polygon = polycomp->body_;
    ak_->DrawPoly(polygon);
  }

  std::set<Entity *> wthTagText = engine_.GetEntityStream().WithTag(Component::Text);
  for (Entity *entity : wthTagText) {
    Text_Component * txtComp = dynamic_cast<Text_Component *>(entity->GetComponent(Component::Text));
    PositionComponent * posComp = dynamic_cast<PositionComponent *>(entity->GetComponent(Component::Position));
    std::string text = txtComp->text + to_string(engine_.GetContext().elapsed_time);
    ak_->DrawString(text, posComp->pos, txtComp->color, txtComp->align, txtComp->huge_font);
  }
}

void RenderSystem::DrawScores() {}

void RenderSystem::Update() {
  if (!engine_.GetContext().screenchange) {
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
