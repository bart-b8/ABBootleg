#include "Menu.h"
#include "Context.h"
#include "Game.h"

menu_actions Menu_item::get_action() {return menu_action;}
std::string Menu_item::get_text() {return text;}

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
            display_menu(START_MENU);
            break;
        case OPEN_LEVELMENU:
            display_menu(LEVEL_MENU);
            break;
        case OPEN_REPLAYMENU:
            display_menu(SCORE_MENU);
            break;
        case BACK:
        case QUIT:
            display_menu(START_MENU);
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
   ak_->ClearScreen();
   ak_->DrawScaledBitmap(SPRT_MENU_BACKGROUND, (float)0, (float)0,
                        Config::Get().Map()["game.background_width"],
                        Config::Get().Map()["game.background_height"],
                        (float)0, (float)0,
                        Config::Get().Map()["game.screen_width"],
                        Config::Get().Map()["game.screen_height"]); 
    Point pos1(Config::Get().Map()["game.screen_width"]/2,Config::Get().Map()["game.screen_height"]-100);
    Point pos2(Config::Get().Map()["game.screen_width"]/2,100);
    double space = (pos1-pos2).Length();
    Color color_selected(255,0,0);
    Color color_notsel(0,0,0);
    size_t size = menu_items.size();

    for (std::vector<Menu_item>::iterator it = menu_items.begin(), int i=0; it != menu_items.end(); ++it, i++) {
        //todo
        Color color;
        if (i!=selected) {
            color=color_notsel;
        } else {
            color=color_selected;
        }
        Point pos(Config::Get().Map()["game.screen_width"]/2,100+(space/(int)size*i))
        ak_->DrawString(it.get_text(),pos,color,ak_->ALIGN_CENTER, true);
    }
}

void Menu::display_menu(menu menu, int index=0) {
    select_menu(menu);
    display_menu(index);
}

void Menu::select_menu(menu menu) {
    create_menu(menu);
}
