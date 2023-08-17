#include "MissileSystem.h"
#include "Missile_CurrentComponent.h"
#include "PositionComponent.h"

void MissileSystem::Update() {
  std::set<Entity *> entities_Current =
      engine_.GetEntityStream().WithTag(Component::Missile_Current);
  if (entities_Current.empty()) {
    return;
  }

  if (!(ak_->IsTimerEvent())) { return; }

  for (Entity *entity : entities_Current) {
    Missile_CurrentComponent *mslcurComponent =
        dynamic_cast<Missile_CurrentComponent *>(
            entity->GetComponent(Component::Missile_Current));
    PositionComponent *mslposComponent =
        dynamic_cast<PositionComponent *>(
            entity->GetComponent(Component::Position));

    mslcurComponent->vel = mslcurComponent->vel + Point(0, -G);
    mslposComponent->pos = mslposComponent->pos + mslcurComponent->vel;

    engine_.GetContext().screenchange = true;

    if (missile_OutOfBounds(mslposComponent->pos)) {
      engine_.RemoveEntity(entity);
      delete entity;
    }
  }
}

bool MissileSystem::missile_OutOfBounds(const Point p) {
  return (p.y_ < -(90+35) || p.y_ > (360) || p.x_ < -35 || p.x_ > 1200);
}
