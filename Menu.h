#ifndef MENU_H
#define MENU_H

#include "Allkit.h"

typedef enum menu {
  START_MENU,
  LEVEL_MENU,
  SCORE_MENU
} menu;

typedef enum menu_actions {
  START_GAME,
  OPEN_PREV,
  OPEN_REPLAY,
  OPEN_LEVELMENU,
  OPEN_REPLAYMENU,
  BACK,
  QUIT
} menu_actions;

/* enum user_actions {
  ENTER,
  UP,
  DOWN,
  ESC
}; */

class Menu_item {
  public:
    Menu_item(std::string text, menu_actions menu_action): text(text), menu_action(menu_action) {};
    menu_actions get_action();

  private:
    std::string text;
    menu_actions menu_action;
};

class Menu {
  public:
    Menu() : ak_(&Allkit::Get()){};

    // Start the menu loop
    void Run();

    void StartGame();

  private:
    Allkit *ak_ = NULL;

    /*Construct menu*/
    void create_menu(menu);

    void action(menu_actions);

    void OpenReplay();

    void display_menu(int index);

    void display_menu(menu, int );

    int selected = 0;

    std::vector<Menu_item> select_menu(menu);

    std::vector<Menu_item> menu_items = select_menu(START_MENU);

  protected:
    bool exit_ = false;
};





#endif
