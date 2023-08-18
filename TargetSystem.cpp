#include "TargetSystem.h"
#include "./PositionComponent.h"
#include "./Target_Component.h"
#include "./Target_BoxComponent.h"
#include "./Target_StoneComponent.h"
#include "./Target_CircleComponent.h"
#include "./Sprite_Component.h"
#include "./Sprite.h" 
#include <fstream>

TargetSystem::TargetSystem(Engine &engine) : System(engine) {
  // read and evaluate level file.
  std::fstream fs(engine_.GetContext().pth_level, std::fstream::in);
  if (!fs.is_open()) {
    engine_.GetContext().exit_game = -1;
    return;
  }

  std::vector<char> targets;

  bool corrupt = false;
  const std::string allowed = "TBS";
  int i = 0;
  while (!fs.eof()) {
    char s;
    fs >> s;
    if (fs.eof()) { break; }
    if (allowed.find(s) != std::string::npos) {
      targets.push_back(s);
      i++;
    } else {
      corrupt = true;
    }
  }
  fs.close();

  if (i != (Config::Get().Map()["level.level_size"] * Config::Get().Map()["level.level_size"])) {
    corrupt = true;
  }

  if (corrupt) {
    engine_.GetContext().exit_game = -2;
    return;
  }


  // Create positions for grid
  Point base(585, 0);
  for (int ii = 0; ii < 64; ii++) {
    int i = ii%8;
    int j = ii/8;
    Point offs(i*35, (8 - 1 - j) * 35);
    Point out = base + offs;
    grid.push_back(out);
  }

  // TODO(BD): generate target entities including positions and add to engine.
  for (long unsigned int i = 0; i < targets.size(); i++) {
    PositionComponent * poscomp = new PositionComponent;
    poscomp->pos = grid[i];
    Target_Component * tgtcomp = new Target_Component;
    tgtcomp->i = i%8;
    tgtcomp->j = i/8;
    tgtcomp->ii = i;
    char s = targets[i];
    Sprite sprite;
    Component *tgttypecomp;
    switch (s) {
      case 'T':
        sprite = Sprite::SPRT_TARGET;
        tgttypecomp = new Target_CircleComponent;
        break;
      case 'B':
        sprite = Sprite::SPRT_BOX;
        tgttypecomp = new Target_BoxComponent;
        break;
      case 'S':
        sprite = Sprite::SPRT_STONE;
        tgttypecomp = new Target_StoneComponent;
        break;
    }

    Sprite_Component * spritecomp = new Sprite_Component;
    spritecomp->sprite = sprite;

    Entity * targetEntity = new Entity;
    targetEntity->Add(poscomp);
    targetEntity->Add(tgtcomp);
    targetEntity->Add(tgttypecomp);
    targetEntity->Add(spritecomp);

    engine_.AddEntity(targetEntity);
  }
}

void TargetSystem::Update() {
  // TODO(BD): check if any missiles are close to any targets.

  // TODO(BD): if yes, hit detection
  // if yes, force perpendiculous to edge. Above certain treshold: second or
  // third target.
  //
  //
  // TODO(BD): flash red when hit then remove:
  // TODO(BD): Check if any targets are no longer supporter. they need to drop
  // down.
}
