#include "Menu.h"
#include "Context.h"
#include "Game.h"

menu_actions Menu_item::get_action() {return menu_action;}

void Menu::Run() {
    exit_ = false;

    display_menu(selected);

    // Menu loop
    while (!exit_) {
        ak_->NextEvent();

        if (ak_->IsArrowKeyUpPushed()) {
            if (selected--!=0) {display_menu(selected);}
            else {selected = 0;}
        }

        if (ak_->IsArrowKeyDownPushed()) {
            if (selected++!=((int)menu_items.size()-1)) {display_menu(selected);}
            else {selected = ((int)menu_items.size()-1);}
        }

        if (ak_->IsEnterKeyPushed()||ak_->IsSpaceBarPushed()) {
            action(menu_items[selected].get_action());
            display_menu(0);
        }

        if (ak_->IsWindowClosed()) {
            exit_ = true;
        }
    }
}

void Menu::create_menu(menu menu) {

    switch(menu) {
        case START_MENU:
            menu_items.push_back(Menu_item("start", OPEN_LEVELMENU));
            menu_items.push_back(Menu_item("replay", OPEN_REPLAYMENU));
            menu_items.push_back(Menu_item("quit", QUIT));
            break;
        case LEVEL_MENU:
            menu_items.push_back(Menu_item("quit", BACK));
            break;
        case SCORE_MENU:
            menu_items.push_back(Menu_item("quit", BACK));
    }
}

void Menu::action (menu_actions menu_action) {
    switch (menu_action) {
        case START_GAME:
            StartGame();
            break;
        case OPEN_PREV:
            select_menu(START_MENU);
            break;
        case OPEN_LEVELMENU:
            select_menu(LEVEL_MENU);
            break;
        case OPEN_REPLAYMENU:
            select_menu(SCORE_MENU);
            break;
        case BACK:
        case QUIT:
            select_menu(START_MENU);
            break;
        case OPEN_REPLAY:
            OpenReplay();
    }
}

void Menu::StartGame() {
    Context context;

    Game game(context);

    game.Run();
}

void Menu::OpenReplay() {
    // TODO
}

void Menu::display_menu(int index) {
    // todo
}

void Menu::display_menu(enum menu, int index=0) {
    // TODO
}

std::vector<Menu_item> Menu::select_menu(enum menu) {
    //TODO
}
