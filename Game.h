#ifndef GAME_H
#define GAME_H

#include "Allkit.h"
#include "Context.h"
#include "Engine.h"
#include <string>

class Game {
 public:
  Game(Context &context) : context_(context),
    engine_(context) {
    ak_ = &Allkit::Get();
  }

  ~Game() {}

  bool Run();

  friend int test_scorescreen();

 private:
  Allkit *ak_ = NULL;
  Context &context_;
  Engine engine_;
  void render_placeholder() const;
  void render_scorescreen(int);
  void render_errorlevelfile();
  void score();
  void writeHighScoreFile(std::string);

};

#endif
