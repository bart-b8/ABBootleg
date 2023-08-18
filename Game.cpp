#include "Game.h"
#include "./Sprite.h"
#include "./Sprite_Component.h"
#include "./Missile_CurrentComponent.h"
#include "./Missile_YellowComponent.h"
#include "MissileSystem.h"
#include "RenderSystem.h"
#include "./PositionComponent.h"
#include "./LauncherSystem.h"
#include "./TargetSystem.h"

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
  context_.exit_game = 0;

  LauncherSystem * launcher = new LauncherSystem(engine_);
  MissileSystem * missileSys = new MissileSystem(engine_);
  TargetSystem * tgtSys = new TargetSystem(engine_);
  RenderSystem * renderer = new RenderSystem(engine_);
  engine_.AddSystem(launcher);
  engine_.AddSystem(missileSys);
  engine_.AddSystem(tgtSys);
  engine_.AddSystem(renderer);

  ak_->StartTimer();

  while (context_.exit_game == 0) {
    engine_.Update();

    ak_->NextEvent();

    if (ak_->IsEnterKeyPushed() || ak_->IsWindowClosed()) {
      context_.exit_game = 1;
    }
  }
  ak_->StopTimer();

  switch (context_.exit_game) {
    case 2:
    // TODO(BD): Show score screen_width
    // TODO(BD): store highscore file.
    break;
    case -1:
    case -2:
      // TODO(BD): show level file error page
      break;
  }

  
  return true;
}
