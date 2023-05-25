#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <algorithm>
#include "Context.h"
#include "EntityStream.h"
#include "System.h"

class Engine {
  private:
  std::vector<Entity*> vec_entitys;
  std::vector<System*> vec_systems;
  EntityStream* entityStream;
  // We got Context by reference shouldn't this be: Context context_ used to be Context * ctx;
  Context context_;

  public:
    Engine(Context &context): context_(context) {}

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