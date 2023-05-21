#ifndef MENU_H
#define MENU_H

#include "Allkit.h"
#include <filesystem>

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
    virtual ~Menu_item() {};
    menu_actions get_action();
    std::string get_text();

    bool operator< (const Menu_item& ) const;
    friend bool grt(Menu_item*, Menu_item*) ;

  protected:
    std::string text;
    menu_actions menu_action;
};

class Level_Menu_item : public Menu_item {
  public: 
    Level_Menu_item(std::string text, menu_actions menu_action, std::filesystem::path path_level) : Menu_item(text, menu_action), path_level(path_level) {};
    virtual ~Level_Menu_item() {};
    std::filesystem::path get_path(); 
  private: 
    std::filesystem::path path_level;

};

class Menu {
  public:
    Menu() : ak_(&Allkit::Get()){};
    ~Menu();

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

    void select_menu(menu);

    void destruct_menu_items();

    std::vector<Menu_item*> menu_items;

  protected:
    bool exit_ = false;
};





#endif
