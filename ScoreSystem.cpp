#include "ScoreSystem.h"
#include "./Engine.h"
#include "./Entity.h"
#include "./PositionComponent.h"
#include "./Text_Component.h"

#include <chrono>

ScoreSystem::ScoreSystem(Engine &engine) : System(engine) {
  // Create text entity with Text en position component
  // Add this to engine
  Text_Component *textComp = new Text_Component;
  PositionComponent *posComp = new PositionComponent;

  textComp->text = "Elepsed Time: ";
  posComp->pos = Point(10, 350);

  Entity *scoreTextEntity = new Entity;

  scoreTextEntity->Add(textComp);
  scoreTextEntity->Add(posComp);

  engine_.AddEntity(scoreTextEntity);

  // Start timer.
  engine_.GetContext().starttime = std::chrono::system_clock::now();
}

void ScoreSystem::Update() {
  std::chrono::duration<double> timeRunning =
      std::chrono::system_clock::now() - engine_.GetContext().starttime;
  int stored_time = engine_.GetContext().elapsed_time;
  if (timeRunning.count() != stored_time) {
    engine_.GetContext().screenchange = true;
    engine_.GetContext().elapsed_time = timeRunning.count();
  }
}
