#include "Game.h"

void Game::Run() {
    Start = true ;
    ak_->StartTimer();
    
    ak_->ClearScreen();
    ak_->DrawScaledBitmap(SPRT_BACKGROUND, (float)0, (float)0,
                Config::Get().Map()["game.background_width"],
                Config::Get().Map()["game.background_height"],
                (float)0, (float)0,
                Config::Get().Map()["game.screen_width"],
                Config::Get().Map()["game.screen_height"]);


    }



