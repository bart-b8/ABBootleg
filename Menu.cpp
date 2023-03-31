#include "Menu.h"
#include "Context.h"
#include "Game.h"

void Menu::Run() {
    exit_ = false;

    // Menu loop
    while (!exit_) {
        ak_->NextEvent();

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
