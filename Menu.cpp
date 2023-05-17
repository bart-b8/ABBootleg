#include "Menu.h"
#include "Context.h"
#include "Game.h"


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
            if (selected++!=(menu_items.size()-1)) {display_menu(selected);}
            else {selected = (menu_items.size()-1);}
        }

        if (ak_->IsEnterKeyPushed()||ak_->IsSpaceBarPushed()) {
            menu_items[selected].action(menu_items[selected].menu_action);
            display_menu(0);
        }

        if (ak_->IsWindowClosed()) {
            exit_ = true;
        }
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

void display_menu(int index) {
    // todo
}

void Menu::display_menu(enum menu, int index=0) {
    // TODO
}

std::vector<Menu_item> Menu::select_menu(enum menu) {
    //TODO
}

bool Menu_item::action (menu_actions menu_action) {
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