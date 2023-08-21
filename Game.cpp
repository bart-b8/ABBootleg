#include "Game.h"
#include "./LauncherSystem.h"
#include "./Missile_CurrentComponent.h"
#include "./Missile_YellowComponent.h"
#include "./PositionComponent.h"
#include "./ScoreSystem.h"
#include "./Sprite.h"
#include "./Sprite_Component.h"
#include "./TargetSystem.h"
#include "HighScore.h"
#include "MissileSystem.h"
#include "RenderSystem.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <istream>
#include <regex>
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
    score();
    break;
  case -1:
  case -2:
    render_errorlevelfile();
    break;
  }

  return true;
}

void Game::score() {
  // while (engine_.GetContext().highscores.size() <
  // Config::Get().Map()["highscores.max_highscores"]) {
  //
  // Collect saved scores.
  std::string highscores_dir = "./assets/highscores";
  std::regex pattern_highscore_file("highscore_[1-9].txt");
  for (const std::filesystem::directory_entry &highscore_dir :
       std::filesystem::directory_iterator(highscores_dir)) {
    if (!std::regex_match(
            static_cast<std::string>(highscore_dir.path().filename()),
            pattern_highscore_file)) {
      break;
    }
    std::fstream highscore_istream(highscore_dir.path(), std::fstream::in);
    if (!highscore_istream.is_open()) {
      std::cerr << "could not open " << highscore_dir.path().filename()
                << std::endl;
      return;
    }

    std::string search = "[SCORE]";
    std::string line;
    int lineNumber = 0;

    while (std::getline(highscore_istream, line)) {
      lineNumber++;
      if (line.find(search) != std::string::npos) {
        if (std::getline(highscore_istream, line)) {
          int score;
          std::istringstream iss(line);
          if (iss >> score) {
            engine_.GetContext().highscores.push_back(
                HighScore(highscore_dir.path(), score));
          } else {
            std::cerr << "Could not extract numberfrom line: "
                      << "Linenumber " << lineNumber + 1 << std::endl;
          }
        }
      }
      if (highscore_istream.bad() || highscore_istream.eof()) {
        break;
      }
    }
    highscore_istream.close();
    // engine_.GetContext();
    // render_scorescreen();
  }

  // Compare score current game to know highscores.
  // If know highscores < config get map 'highscores.max_highscores'
  // then: add to highscores in correct position by renaming all files to get
  // bumped and then store the highscore file.
  int score = engine_.GetContext().elapsed_time;
  std::list<HighScore> highscores = engine_.GetContext().highscores;
  std::vector<HighScore> vector_highscores;
  int new_highscore = -1;
  highscores.sort();
  int i = 0;
  for (HighScore a : highscores) {
    i++;
    if (score < a.score && new_highscore == -1) {
      new_highscore = i;
    }
    vector_highscores.push_back(a);
  }
  if (new_highscore == -1 &&
      highscores.size() < Config::Get().Map()["highscores.max_highscores"]) {
    new_highscore = highscores.size() + 1;
  }

  if (new_highscore != -1) {
    // Number of highscore files is equal to highscores.max_highscores then
    // remove file
    if (highscores.size() == Config::Get().Map()["highscores.max_highscores"]) {
      std::string file_to_remove =
          vector_highscores[highscores.size() - 1].highscore_file_dir;
      std::filesystem::remove(file_to_remove);
      highscores.pop_back();
    }
    for (int i = highscores.size(); i >= new_highscore; --i) {
      std::string old_name =
          highscores_dir + "/highscore_" + to_string(i) + ".txt";
      std::string new_name =
          highscores_dir + "/highscore_" + to_string(i + 1) + ".txt";
      std::filesystem::rename(old_name, new_name);
    }

    std::string new_highscoreFile =
        highscores_dir + "/highscore_" + to_string(new_highscore) + ".txt";
    writeHighScoreFile(new_highscoreFile);
    render_scorescreen(new_highscore);

    // TODO(BD): Update checksum.
  }
}

void Game::writeHighScoreFile(std::string file) {
  std::ofstream new_highscoreFileStream(file);
  if (!new_highscoreFileStream.is_open()) {
    return;
  }

  new_highscoreFileStream << "[LEVEL]" << endl;
  new_highscoreFileStream << engine_.GetContext().pth_level << endl;
  new_highscoreFileStream << "[SCORE]" << endl;
  new_highscoreFileStream << engine_.GetContext().elapsed_time;

  new_highscoreFileStream.close();
}

void Game::render_scorescreen(int highscore_place) {
  ak_->ClearScreen();
  ak_->DrawScaledBitmap(SPRT_BACKGROUND, (float)0, (float)0,
                        Config::Get().Map()["game.background_width"],
                        Config::Get().Map()["game.background_height"], (float)0,
                        (float)0, Config::Get().Map()["game.screen_width"],
                        Config::Get().Map()["game.screen_height"]);
  std::string text1 = "Game Complete. With Score: " +
                      to_string(engine_.GetContext().elapsed_time);
  std::string text2 = "Press Enter||Space to go back.";
  Point pos1(Config::Get().Map()["game.screen_width"] / 2,
             Config::Get().Map()["game.screen_height"] - 150);
  Point pos2(Config::Get().Map()["game.screen_width"] / 2,
             Config::Get().Map()["game.screen_height"] - 350);
  Color color(0, 0, 0);

  if (highscore_place != -1) {
    std::string text3 = "New Highscore. Place: " + to_string(highscore_place);
    Point pos3(Config::Get().Map()["game.screen_width"] / 2,
               Config::Get().Map()["game.screen_height"] - 220);
    ak_->DrawString(text3, pos3, color, ak_->ALIGN_CENTER, false);
  }
  ak_->DrawString(text1, pos1, color, ak_->ALIGN_CENTER, false);
  ak_->DrawString(text2, pos2, color, ak_->ALIGN_CENTER, false);
  ak_->DrawOnScreen(true);

  bool exit_ = false;
  while (!exit_) {
    ak_->NextEvent();

    if (ak_->IsWindowClosed() || ak_->IsEnterKeyPushed() ||
        ak_->IsSpaceBarPushed()) {
      exit_ = true;
    }
  }
}

void Game::render_errorlevelfile() {
  ak_->ClearScreen();
  ak_->DrawScaledBitmap(SPRT_BACKGROUND, (float)0, (float)0,
                        Config::Get().Map()["game.background_width"],
                        Config::Get().Map()["game.background_height"], (float)0,
                        (float)0, Config::Get().Map()["game.screen_width"],
                        Config::Get().Map()["game.screen_height"]);
  std::string text1 = "Error with loading selected level file.";
  std::string text2 = "Press Enter||Space to go back.";
  Point pos1(Config::Get().Map()["game.screen_width"] / 2,
             Config::Get().Map()["game.screen_height"] - 150);
  Point pos2(Config::Get().Map()["game.screen_width"] / 2,
             Config::Get().Map()["game.screen_height"] - 350);
  Color color(0, 0, 0);

  ak_->DrawString(text1, pos1, color, ak_->ALIGN_CENTER, false);
  ak_->DrawString(text2, pos2, color, ak_->ALIGN_CENTER, false);
  ak_->DrawOnScreen(true);

  bool exit_ = false;
  while (!exit_) {
    ak_->NextEvent();

    if (ak_->IsWindowClosed() || ak_->IsEnterKeyPushed() ||
        ak_->IsSpaceBarPushed()) {
      exit_ = true;
    }
  }
}
