#ifndef ENTITYSTREAM_H
#define ENTITYSTREAM_H

#include <set>
#include <map>
#include "Entity.h"
#include "Component.h"
#include "algorithm"

class EntityStream {
  private:
    std::map <Component::Tag, std::set<Entity*>> map_entitys;

  public:
    std::set<Entity *> WithTag(Component::Tag tag);

    std::set<Entity *> WithTags(std::set<Component::Tag> &tags);

    void EntityUpdated(Entity *entity, std::vector<Component::Tag> &tags, bool remove);
};

#endif
