#ifndef SCORESYS
#define SCORESYS

#include "./System.h"

class ScoreSystem : public System {
 public:
  ScoreSystem(Engine &engine);

  void Update();

};
#endif // !SCORESYS
