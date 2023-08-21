#include "Game.h"
#include "./LauncherSystem.h"
#include "./Missile_CurrentComponent.h"
#include "./Missile_YellowComponent.h"
#include "./PositionComponent.h"
#include "./Sprite.h"
#include "./Sprite_Component.h"
#include "./TargetSystem.h"
#include "MissileSystem.h"
#include "RenderSystem.h"
#include "./ScoreSystem.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <istream>
#include <sstream>

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

  LauncherSystem *launcher = new LauncherSystem(engine_);
  MissileSystem *missileSys = new MissileSystem(engine_);
  TargetSystem *tgtSys = new TargetSystem(engine_);
  ScoreSystem *scrSys = new ScoreSystem(engine_);
  RenderSystem *renderer = new RenderSystem(engine_);
  engine_.AddSystem(launcher);
  engine_.AddSystem(missileSys);
  engine_.AddSystem(tgtSys);
  engine_.AddSystem(scrSys);
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
    score();
    render_scorescreen();
    // TODO(BD): store highscore file.
    break;
  case -1:
  case -2:
    // TODO(BD): show level file error page
    break;
  }

  return true;
}

void Game::score() {
  // while (engine_.GetContext().highscores.size() <
  // Config::Get().Map()["highscores.max_highscores"]) {
  std::string highscores_dir = "./assets/highscores";
  for (const std::filesystem::directory_entry &highscore_dir :
       std::filesystem::directory_iterator(highscores_dir)) {
    std::fstream fs(highscore_dir.path(), std::fstream::in);
    if (!fs.is_open()) { break; }
    char s[8];
    fs.getline(s, 8);
    int score;
    while (strcmp(s,"[SCORE]") != 0) {
      fs.getline(s,8);
    }
       fs >> score;

  }
  // engine_.GetContext();
  // render_scorescreen();
}
void Game::render_scorescreen() {
  ak_->ClearScreen();
  ak_->DrawScaledBitmap(SPRT_BACKGROUND, (float)0, (float)0,
                        Config::Get().Map()["game.background_width"],
                        Config::Get().Map()["game.background_height"], (float)0,
                        (float)0, Config::Get().Map()["game.screen_width"],
                        Config::Get().Map()["game.screen_height"]);
  std::string text1 =
      "Game Complete. With Score: " + (std::string)context_.pth_level.stem();
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
