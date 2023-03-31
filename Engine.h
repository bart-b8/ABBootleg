#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include "Context.h"
#include "EntityStream.h"
#include "System.h"

class Engine {
  public:
    Engine(Context &context) {}

    void AddEntity(Entity *entity);

    void UpdateEntity(Entity *entity, std::vector<Component::Tag> &tags, bool remove);

    std::vector<Entity *>::iterator RemoveEntity(Entity *entity);

    void AddSystem(System *system);

    std::vector<System *>::iterator RemoveSystem(System *system);

    std::vector<Entity *> &GetEntities();

    EntityStream &GetEntityStream();

    Context &GetContext();

    void Update();
};

#endif