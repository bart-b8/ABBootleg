#include "TargetSystem.h"
#include "./PositionComponent.h"
#include "./Sprite.h"
#include "./Sprite_Component.h"
#include "./Target_BoxComponent.h"
#include "./Target_CircleComponent.h"
#include "./Target_Component.h"
#include "./Target_StoneComponent.h"
#include "Component.h"
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
    if (fs.eof()) {
      break;
    }
    if (allowed.find(s) != std::string::npos) {
      targets.push_back(s);
      i++;
    } else {
      corrupt = true;
    }
  }
  fs.close();

  if (i != (Config::Get().Map()["level.level_size"] *
            Config::Get().Map()["level.level_size"])) {
    corrupt = true;
  }

  if (corrupt) {
    engine_.GetContext().exit_game = -2;
    return;
  }

  // Create positions for grid
  Point base(585, 0);
  for (int ii = 0; ii < 64; ii++) {
    int i = ii % 8;
    int j = ii / 8;
    Point offs(i * 35, (8 - 1 - j) * 35);
    Point out = base + offs;
    grid.push_back(out);
  }

  // generate target entities including positions and add to engine.
  for (long unsigned int i = 0; i < targets.size(); i++) {
    PositionComponent *poscomp = new PositionComponent;
    poscomp->pos = grid[i];
    Target_Component *tgtcomp = new Target_Component;
    tgtcomp->i = i % 8;
    tgtcomp->j = i / 8;
    tgtcomp->ii = i;
    char s = targets[i];
    Sprite sprite;
    Sprite hit;
    Component *tgttypecomp;
    switch (s) {
    case 'T':
      sprite = Sprite::SPRT_TARGET;
      tgttypecomp = new Target_CircleComponent;
      hit = Sprite::SPRT_TARGET_HIT;
      break;
    case 'B':
      sprite = Sprite::SPRT_BOX;
      tgttypecomp = new Target_BoxComponent;
      hit = Sprite::SPRT_BOX_HIT;
      break;
    case 'S':
      sprite = Sprite::SPRT_STONE;
      tgttypecomp = new Target_StoneComponent;
      hit = Sprite::SPRT_STONE_HIT;
      break;
    }

    Sprite_Component *spritecomp = new Sprite_Component;
    spritecomp->sprite = sprite;

    tgtcomp->normal = sprite;
    tgtcomp->hit = hit;

    Entity *targetEntity = new Entity;
    targetEntity->Add(poscomp);
    targetEntity->Add(tgtcomp);
    targetEntity->Add(tgttypecomp);
    targetEntity->Add(spritecomp);

    engine_.AddEntity(targetEntity);
  }
}

void TargetSystem::Update() {
  // check if any missiles are close to any targets.
  std::set<Entity *> currmiss_set =
      engine_.GetEntityStream().WithTag(Component::Missile_Current);
  std::set<Entity *> tgt_set =
      engine_.GetEntityStream().WithTag(Component::Target);

  for (Entity *currmiss : currmiss_set) {
    Point pos_miss = dynamic_cast<PositionComponent *>(
                         currmiss->GetComponent(Component::Position))
                         ->pos;
    for (Entity *tgt : tgt_set) {
      Point pos_tgt = dynamic_cast<PositionComponent *>(
                          tgt->GetComponent(Component::Position))
                          ->pos;

      if ((pos_miss * pos_tgt) < 50) {
        // TODO(BD) hit detection improve
        AddToCollidedMissiles(currmiss);
        AddToHitTargets(tgt);
      }
    }
  }

  // TODO(BD): if yes, hit detection
  // if yes, force perpendiculous to edge. Above certain treshold: second or
  // third target.
  if (ak_->IsTimerEvent()) {
    Update_collided_Missiles();
    Update_hit_tgts();

    // Test if there are still round targets if not: end game and show score
    // screen.
    if (engine_.GetEntityStream().WithTag(Component::Target_Circle).empty()) {
      engine_.GetContext().exit_game = 2;
    }
  }
}

void TargetSystem::AddToCollidedMissiles(Entity *currmiss) {
  if (IsIn(collided_missiles, currmiss)) {
    return;
  }
  collided_missiles[currmiss] = 0;
}
void TargetSystem::AddToHitTargets(Entity *tgt) {
  if (IsIn(hit_tgts, tgt)) {
    return;
  }
  hit_tgts[tgt] = 0;
}

bool TargetSystem::IsIn(std::map<Entity *, int> map, Entity *enty) {
  return (map.find(enty) != map.end());
}

void TargetSystem::Update_collided_Missiles() {
  for (auto [enty, count] : collided_missiles) {
    count++;
    if (count >= 1) {
      engine_.RemoveEntity(enty);
      collided_missiles.erase(enty);
      delete enty;
    }
  }
}

void TargetSystem::Update_hit_tgts() {
  for (auto [enty, count] : hit_tgts) {
    hit_tgts[enty] = count + 1;
    /* std::cout << "count is: " << count << "\t And comses to \t"
              << count / 30 % 2 << endl; */

    if (count / 20 % 2 == 0) {
      engine_.GetContext().screenchange = true;
      dynamic_cast<Sprite_Component *>(enty->GetComponent(Component::Sprite))
          ->sprite = dynamic_cast<Target_Component *>(
                         enty->GetComponent(Component::Target))
                         ->hit;
    } else if (count / 20 % 2 == 1) {
      engine_.GetContext().screenchange = true;
      dynamic_cast<Sprite_Component *>(enty->GetComponent(Component::Sprite))
          ->sprite = dynamic_cast<Target_Component *>(
                         enty->GetComponent(Component::Target))
                         ->normal;
    }
    if (count > 120) {
      engine_.GetContext().screenchange = true;
      engine_.RemoveEntity(enty);
      hit_tgts.erase(enty);
      // take targetCompoennt i , j and ii value and make sure to drop
      // all targets on top.
      int i = dynamic_cast<Target_Component *>(
                  enty->GetComponent(Component::Target))
                  ->i;
      int j = dynamic_cast<Target_Component *>(
                  enty->GetComponent(Component::Target))
                  ->j;
      int ii = dynamic_cast<Target_Component *>(
                   enty->GetComponent(Component::Target))
                   ->ii;
      DropSupportedTargets(i, j, ii);
      delete enty;

      // TODO(BD): remove. This is only for testing purposuos.
      engine_.GetContext().exit_game = 2;
    }
  }
}

void TargetSystem::DropSupportedTargets(int i, int j, int ii) {
  std::set<Entity *> tgts =
      engine_.GetEntityStream().WithTag(Component::Target);
  for (Entity *tgt : tgts) {
    Target_Component *tgtcomp =
        dynamic_cast<Target_Component *>(tgt->GetComponent(Component::Target));
    if (tgtcomp->i == i && tgtcomp->j < j) {
      tgtcomp->j += 1;
      PositionComponent *poscomp = dynamic_cast<PositionComponent *>(
          tgt->GetComponent(Component::Position));
      poscomp->pos = grid[tgtcomp->i + tgtcomp->j * 8];
    }
  }
}
