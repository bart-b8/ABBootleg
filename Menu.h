#ifndef MENU_H
#define MENU_H

#include "Allkit.h"

enum menu {
  START_MENU,
  LEVEL_MENU,
  SCORE_MENU
};

enum menu_actions {
  START_GAME,
  OPEN_PREV,
  OPEN_REPLAY,
  OPEN_LEVELMENU,
  OPEN_REPLAYMENU,
  BACK,
  QUIT

};

class Menu_item {
  public:
    Menu_item(std::string text, enum menu_actions): text(text), menu_actions(menu_actions) {};
    bool action(enum menu_actions=menu_actions);
  private:
    std::string text;
    int menu_actions;
};

class Menu {
  public:
    Menu() : ak_(&Allkit::Get()){};

    // Start the menu loop
    void Run();

    void StartGame();

  private:
    Allkit *ak_ = NULL;

    int selected = 0;

    std::vector<Menu_item> menu_items = select_menu(START_MENU);

    std::vector<Menu_item> select_menu(enum menu);

    void display_menu(int index);

    void display_menu(enum menu, int index=0);

  protected:
    bool exit_ = false;
};

/* Create Menu's */
std::vector<Menu_item> start_menu, level_menu, score_menu;

/*Construct start_menu*/
void create_start_menu(std::vector<Menu_item> start_menu) {
start_menu.push_back(Menu_item("start", OPEN_LEVELMENU));
start_menu.push_back(Menu_item("replay", OPEN_REPLAYMENU));
start_menu.push_back(Menu_item("quit", QUIT));
};

/*Construct level_menu*/
void create_level_menu(std::vector<Menu_item> level_menu) {
level_menu.push_back(Menu_item("quit", BACK));
};

/*Construct score_menu*/
void create_level_menu(std::vector<Menu_item> score_menu) {
score_menu.push_back(Menu_item("quit", BACK));
};


#endif
