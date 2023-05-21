#ifndef GAME_H
#define GAME_H

#include "Allkit.h"
#include "Context.h"
#include "Engine.h"

class Game {
  public:
    Game(Context &context) : context_(context),
                             engine_(context) {
        ak_ = &Allkit::Get();
    };

    ~Game(){
        // TODO
    };

    bool Run();
  

  private:
    Allkit *ak_ = NULL;
    Context &context_;
    Engine engine_;
    void render_placeholder() const;
};

#endif