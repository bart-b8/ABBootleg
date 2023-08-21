#include "Menu.h"
#include "Context.h"
#include "Game.h"
#include "HighScore.h"
#include <algorithm>
#include <filesystem>
#include <regex>

// namespace fs=std::filesystem;

menu_actions Menu_item::get_action() { return menu_action; }
std::string Menu_item::get_text() { return text; }
std::filesystem::path Level_Menu_item::get_path() { return path_level; }

bool Menu_item::operator<(const Menu_item &rhs_) const {
  return (text < rhs_.text);
}

bool grt(Menu_item *lhs, Menu_item *rhs) {
  std::string text_left = lhs->get_text();
  std::string text_right = rhs->get_text();

  return (text_left < text_right);
}

Menu::Menu(): ak_(&Allkit::Get()) {}

Menu::~Menu() { destruct_menu_items(); }

void Menu::Run() {
  exit_ = false;

  select_menu(START_MENU);
  display_menu(selected);

  // Menu loop
  while (!exit_) {
    ak_->NextEvent();

    if (ak_->IsArrowKeyUpPushed()) {
      if (selected-- != 0) {
        display_menu(selected);
      } else {
        selected = 0;
      }
    }

    if (ak_->IsArrowKeyDownPushed()) {
      if (selected++ != ((int)menu_items.size() - 1)) {
        display_menu(selected);
      } else {
        selected = ((int)menu_items.size() - 1);
      }
    }

    if (ak_->IsEnterKeyPushed() || ak_->IsSpaceBarPushed()) {
      action(menu_items[selected]->get_action());
    }

    if (ak_->IsWindowClosed()) {
      exit_ = true;
    }
  }
}

void Menu::create_menu(menu menu) {
  switch (menu) {
  case START_MENU: {
    destruct_menu_items();
    Menu_item *ptr_menu_item = new Menu_item("start", OPEN_LEVELMENU);
    menu_items.push_back(ptr_menu_item);
    ptr_menu_item = new Menu_item("replay", OPEN_REPLAYMENU);
    menu_items.push_back(ptr_menu_item);
    ptr_menu_item = new Menu_item("quit", QUIT);
    menu_items.push_back(ptr_menu_item);

    break;
  }
  case LEVEL_MENU: {
    destruct_menu_items();
    std::string levels_dir = "./assets/levels";
    Menu_item *ptr_menu_item;
    for (const std::filesystem::directory_entry &level_dir :
         std::filesystem::directory_iterator(levels_dir)) {
      std::string filename = level_dir.path().stem();
      ptr_menu_item =
          new Level_Menu_item(filename, START_GAME, level_dir.path());
      menu_items.push_back(ptr_menu_item);
    }
    std::sort(menu_items.begin(), menu_items.end(), grt);
    ptr_menu_item = new Menu_item("quit", BACK);
    menu_items.push_back(ptr_menu_item);
    break;
  }
  case SCORE_MENU:
    destruct_menu_items();
    UpdateHighScores();
    std::string highscores_dir = "./assets/highscores";
    Menu_item *ptr_menu_item;

    for (HighScore highscore : context_.highscores) {
      std::filesystem::path filename_path = std::filesystem::path(highscore.highscore_file_dir);
      ptr_menu_item = new Level_Menu_item(filename_path.stem(), OPEN_REPLAY, filename_path);
      menu_items.push_back(ptr_menu_item);
    }
    ptr_menu_item = new Menu_item("quit", BACK);
    menu_items.push_back(ptr_menu_item);
  }
}

void Menu::action(menu_actions menu_action) {
  switch (menu_action) {
  case START_GAME:
    StartGame();
    display_menu(LEVEL_MENU, 0);
    break;
  case OPEN_PREV:
    display_menu(START_MENU, 0);
    break;
  case OPEN_LEVELMENU:
    display_menu(LEVEL_MENU, 0);
    break;
  case OPEN_REPLAYMENU:
    display_menu(SCORE_MENU, 0);
    break;
  case BACK:
    display_menu(START_MENU, 0);
    break;
  case QUIT:
    exit_ = true;
    break;
  case OPEN_REPLAY:
    OpenReplay();
    display_menu(SCORE_MENU, selected);
  }
}

void Menu::StartGame() {
  // Set level path in context:
  // create class based on Menu_item for level menu items that include the path
  // to level file.
  Level_Menu_item *ptr_selected =
      dynamic_cast<Level_Menu_item *>(menu_items[selected]);
  context_.pth_level = ptr_selected->get_path();

  Game game(context_);

  game.Run();
}

void Menu::OpenReplay() {
  Level_Menu_item *ptr_selected = dynamic_cast<Level_Menu_item *>(menu_items[selected]);
  for (HighScore highscore : context_.highscores) {
    if (highscore.highscore_file_dir == ptr_selected->get_path()) {
      ShowHighScoreInfo(highscore.level_file_dir, highscore.score);
    }
  }
  while (true) {
    ak_->NextEvent();
    if (ak_->IsEnterKeyPushed() || ak_->IsSpaceBarPushed()) {
      break;
    }
  }
}

void Menu::ShowHighScoreInfo(std::filesystem::path level_path, int score) {
  ak_->ClearScreen();
  ak_->DrawScaledBitmap(SPRT_BACKGROUND, (float)0, (float)0,
                        Config::Get().Map()["game.background_width"],
                        Config::Get().Map()["game.background_height"], (float)0,
                        (float)0, Config::Get().Map()["game.screen_width"],
                        Config::Get().Map()["game.screen_height"]);
  std::string text1 =
      "Highscore for: " + (std::string)level_path.stem();
  std::string text2 = "With a score: " + to_string(score);
  std::string text3 = "Press Enter||Space to go back.";
  Point pos1(Config::Get().Map()["game.screen_width"] / 2,
             Config::Get().Map()["game.screen_height"] - 180);
  Point pos2(Config::Get().Map()["game.screen_width"] / 2,
             Config::Get().Map()["game.screen_height"] - 250);
  Point pos3(Config::Get().Map()["game.screen_width"] / 2,
             Config::Get().Map()["game.screen_height"] - 320);
  Color color(0, 0, 0);
  ak_->DrawString(text1, pos1, color, ak_->ALIGN_CENTER, false);
  ak_->DrawString(text2, pos2, color, ak_->ALIGN_CENTER, false);
  ak_->DrawString(text3, pos3, color, ak_->ALIGN_CENTER, false);
  ak_->DrawOnScreen(true);
}

void Menu::display_menu(int index) {
  ak_->ClearScreen();
  selected = index;
  ak_->DrawScaledBitmap(SPRT_MENU_BACKGROUND, (float)0, (float)0,
                        Config::Get().Map()["game.background_width"],
                        Config::Get().Map()["game.background_height"], (float)0,
                        (float)0, Config::Get().Map()["game.screen_width"],
                        Config::Get().Map()["game.screen_height"]);
  Point pos1(Config::Get().Map()["game.screen_width"] / 2,
             Config::Get().Map()["game.screen_height"] - 180);
  Point pos2(Config::Get().Map()["game.screen_width"] / 2, -20);
  double space = pos1 * pos2;
  Color color_selected(255, 0, 0);
  Color color_notsel(0, 0, 0);
  size_t size = menu_items.size();

  for (int i = 0; i < (int)size; i++) {
    Point pos;
    Color color;
    if (i != selected) {
      color = color_notsel;
    } else {
      color = color_selected;
    }
    if (size != 1) {
      pos.x_ = pos1.x_;
      pos.y_ = pos1.y_ - (i * space / (size - 1));
    } else {
      pos = pos2;
    }
    std::string text = menu_items[i]->get_text();
    ak_->DrawString(text, pos, color, ak_->ALIGN_CENTER, false);
  }
  ak_->DrawOnScreen(true);
}

void Menu::display_menu(menu menu, int index = 0) {
  select_menu(menu);
  display_menu(index);
}

void Menu::select_menu(menu menu) { create_menu(menu); }

void Menu::destruct_menu_items() {
  for (const auto ptr : menu_items) {
    delete ptr;
  }
  menu_items.clear();
}

void Menu::UpdateHighScores() {
  context_.highscores.clear();
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
            context_.highscores.push_back(
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
  }
  context_.highscores.sort();
}
