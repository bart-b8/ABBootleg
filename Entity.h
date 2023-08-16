#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <algorithm>

#include "Component.h"

class Entity {
  private:
    std::vector<Component*> vec_comps;
    std::vector<Component::Tag> vec_tags;

  public:
    void Add(Component *component);

    void Remove(Component *component);

    Component *GetComponent(Component::Tag tag);

    std::vector<Component *> &GetComponents();

    std::vector<Component::Tag> &GetTags();

  ~Entity();
};

#endif
