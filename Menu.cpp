#include "Menu.h"
#include "Context.h"
#include "Game.h"
#include <filesystem>
#include <algorithm>
// namespace fs=std::filesystem;

menu_actions Menu_item::get_action() {return menu_action;}
std::string Menu_item::get_text() {return text;}
std::filesystem::path Level_Menu_item::get_path() {return path_level;}

bool Menu_item::operator< (const Menu_item& rhs_) const {
    return (text < rhs_.text);
}

bool grt(Menu_item* lhs, Menu_item* rhs) {
    std::string text_left = lhs->get_text();
    std::string text_right = rhs->get_text();

    return (text_left < text_right);
}

Menu::~Menu() {
    destruct_menu_items();
}

void Menu::Run() {
    exit_ = false;

    select_menu(START_MENU);
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
            action(menu_items[selected]->get_action());
        }

        if (ak_->IsWindowClosed()) {
            exit_ = true;
        }
    }
}

void Menu::create_menu(menu menu) {

    switch(menu) {
        case START_MENU: {
            destruct_menu_items();
            Menu_item* ptr_menu_item = new Menu_item("start", OPEN_LEVELMENU);
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
            Menu_item* ptr_menu_item;
            for (const std::filesystem::directory_entry & level_dir : std::filesystem::directory_iterator(levels_dir)) {
                std::string filename = level_dir.path().stem();
                ptr_menu_item = new Level_Menu_item(filename, START_GAME, level_dir.path());
                menu_items.push_back(ptr_menu_item);
            };
            std::sort(menu_items.begin(),menu_items.end(),grt);
            ptr_menu_item = new Menu_item("quit", BACK);
            menu_items.push_back(ptr_menu_item);
            break;
            }
        case SCORE_MENU:
            destruct_menu_items();
            std::string highscores_dir = "./assets/highscores";
            Menu_item* ptr_menu_item;
            for (const std::filesystem::directory_entry & highscore_dir : std::filesystem::directory_iterator(highscores_dir)) {
                std::string filename = highscore_dir.path().stem();
                if (filename!="checksum") {
                    ptr_menu_item = new Level_Menu_item(filename, OPEN_REPLAY, highscore_dir.path());
                    menu_items.push_back(ptr_menu_item);
                }
            }
            std::sort(menu_items.begin(),menu_items.end(),grt);
            ptr_menu_item = new Menu_item("quit", BACK);
            menu_items.push_back(ptr_menu_item);
    }
}

void Menu::action (menu_actions menu_action) {
    switch (menu_action) {
        case START_GAME:
            StartGame();
            display_menu(START_MENU,0);
            break;
        case OPEN_PREV:
            display_menu(START_MENU,0);
            break;
        case OPEN_LEVELMENU:
            display_menu(LEVEL_MENU,0);
            break;
        case OPEN_REPLAYMENU:
            display_menu(SCORE_MENU,0);
            break;
        case BACK:
            display_menu(START_MENU,0);
            break;
        case QUIT:
            exit_ = true;
            break;
        case OPEN_REPLAY:
            OpenReplay();
    }
}

void Menu::StartGame() {
    Context context;

    // Set level path in context: 
    // create class based on Menu_item for level menu items that include the path to level file. 
    Level_Menu_item *ptr_selected = dynamic_cast<Level_Menu_item*>(menu_items[selected]);
    context.pth_level=ptr_selected->get_path();


    Game game(context);

    game.Run();
}

void Menu::OpenReplay() {
    // TODO
}

void Menu::display_menu(int index) {
   ak_->ClearScreen();
   selected = index;
   ak_->DrawScaledBitmap(SPRT_MENU_BACKGROUND, (float)0, (float)0,
                        Config::Get().Map()["game.background_width"],
                        Config::Get().Map()["game.background_height"],
                        (float)0, (float)0,
                        Config::Get().Map()["game.screen_width"],
                        Config::Get().Map()["game.screen_height"]); 
    Point pos1(Config::Get().Map()["game.screen_width"]/2,Config::Get().Map()["game.screen_height"]-180);
    Point pos2(Config::Get().Map()["game.screen_width"]/2,-20);
    double space = pos1*pos2;
    Color color_selected(255,0,0);
    Color color_notsel(0,0,0);
    size_t size = menu_items.size();

    for (int i=0; i<(int)size; i++) {
        Point pos;
        Color color;
        if (i!=selected) {
            color=color_notsel;
        } else {
            color=color_selected;
        }
        if (size!=1) {
            pos.x_=pos1.x_;
            pos.y_=pos1.y_-(i*space/(size-1));
        } else {
            pos = pos2;
        }
        std::string text = menu_items[i]->get_text();
        ak_->DrawString(text,pos,color,ak_->ALIGN_CENTER, false);
    }
    ak_->DrawOnScreen(true);
}

void Menu::display_menu(menu menu, int index=0) {
    select_menu(menu);
    display_menu(index);
}

void Menu::select_menu(menu menu) {
    create_menu(menu);
}

void Menu::destruct_menu_items() {
    for (const auto ptr : menu_items) {
        delete ptr;
    }
    menu_items.clear();
}
