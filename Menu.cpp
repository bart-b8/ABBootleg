#include "Menu.h"
#include "Context.h"
#include "Game.h"

void Menu::Run() {
    exit_ = false;

    display_menu(START_MENU);

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
            menu_items[selected].action();
            display_menu(0);
        }
        
        // continiue:

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
