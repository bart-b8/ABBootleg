#include "Game.h"

void Game::render_placeholder() const {
    ak_->ClearScreen();
    ak_->DrawScaledBitmap(SPRT_BACKGROUND, (float)0, (float)0,
                        Config::Get().Map()["game.background_width"],
                        Config::Get().Map()["game.background_height"],
                        (float)0, (float)0,
                        Config::Get().Map()["game.screen_width"],
                        Config::Get().Map()["game.screen_height"]); 
    std::string text1 = "Placeholder for: " + (std::string)context_.pth_level.stem();
    std::string text2 = "Press Enter||Space to go back.";
    Point pos1(Config::Get().Map()["game.screen_width"]/2,Config::Get().Map()["game.screen_height"]-180);
    Point pos2(Config::Get().Map()["game.screen_width"]/2,Config::Get().Map()["game.screen_height"]-250);
    Color color(0,0,0);
    ak_->DrawString(text1,pos1,color,ak_->ALIGN_CENTER, false);
    ak_->DrawString(text2,pos2,color,ak_->ALIGN_CENTER, false);
    ak_->DrawOnScreen(true);
}

bool Game::Run() {
    // TODO
    render_placeholder();
    bool exit_ = false;
    while(!exit_) {
        ak_->NextEvent();

        if (ak_->IsEnterKeyPushed()||ak_->IsSpaceBarPushed()) {
            exit_=true;
        }

    }

    return true;
}
