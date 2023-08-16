#include "Game.h"
#include "./Sprite.h"
#include "./Sprite_Component.h"
#include "./Missile_CurrentComponent.h"
#include "./Missile_YellowComponent.h"
#include "RenderSystem.h"
#include "./PositionComponent.h"

// Deprecated. Should not be needed anymore after v0.1
void Game::render_placeholder() const {
  ak_->ClearScreen();
  ak_->DrawScaledBitmap(SPRT_BACKGROUND, (float)0, (float)0,
                        Config::Get().Map()["game.background_width"],
                        Config::Get().Map()["game.background_height"], (float)0,
                        (float)0, Config::Get().Map()["game.screen_width"],
                        Config::Get().Map()["game.screen_height"]);
  std::string text1 =
      "Placeholder for: " + (std::string)context_.pth_level.stem();
  std::string text2 = "Press Enter||Space to go back.";
  Point pos1(Config::Get().Map()["game.screen_width"] / 2,
             Config::Get().Map()["game.screen_height"] - 180);
  Point pos2(Config::Get().Map()["game.screen_width"] / 2,
             Config::Get().Map()["game.screen_height"] - 250);
  Color color(0, 0, 0);
  ak_->DrawString(text1, pos1, color, ak_->ALIGN_CENTER, false);
  ak_->DrawString(text2, pos2, color, ak_->ALIGN_CENTER, false);
  ak_->DrawOnScreen(true);
}

bool Game::Run() {
  // TODO(BD) : Implement simple game.
  bool exit_ = false;
  Entity * missile = new Entity;
  Missile_CurrentComponent * missile_current = new Missile_CurrentComponent;
  Missile_YellowComponent * missile_yellow = new Missile_YellowComponent;
  Sprite_Component * sprite = new Sprite_Component;
  PositionComponent * pos = new PositionComponent;
  pos->pos.x_ = 200;
  pos->pos.y_ = 200;
  sprite->sprite = Sprite::SPRT_MISSILE_1;
  pos->pos.x_ = 0;
  pos->pos.y_ = 100;
  missile->Add(missile_current);
  missile->Add(missile_yellow);
  missile->Add(sprite);
  missile->Add(pos);
  engine_.AddEntity(missile);

  RenderSystem * renderer = new RenderSystem(engine_);
  engine_.AddSystem(renderer);

  while (!exit_) {
    engine_.Update();

    ak_->NextEvent();

    if (ak_->IsEnterKeyPushed() || ak_->IsSpaceBarPushed()) {
      exit_ = true;
    }
  }
  return true;
}
