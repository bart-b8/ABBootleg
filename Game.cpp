#include "Game.h"
#include "./Sprite.h"
#include "./Sprite_Component.h"
#include "./Missile_CurrentComponent.h"
#include "./Missile_YellowComponent.h"
#include "MissileSystem.h"
#include "RenderSystem.h"
#include "./PositionComponent.h"
#include "./LauncherSystem.h"

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

  LauncherSystem * launcher = new LauncherSystem(engine_);
  MissileSystem * missileSys = new MissileSystem(engine_);
  RenderSystem * renderer = new RenderSystem(engine_);
  engine_.AddSystem(launcher);
  engine_.AddSystem(missileSys);
  engine_.AddSystem(renderer);

  ak_->StartTimer();

  while (!exit_) {
    engine_.Update();

    ak_->NextEvent();

    if (ak_->IsEnterKeyPushed() || ak_->IsWindowClosed()) {
      ak_->StopTimer();
      exit_ = true;
    }
  }
  return true;
}
