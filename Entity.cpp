#include "Entity.h"



void Entity::Add(Component* component) {
    Comps.push_back(component);
}

void Entity::Remove(Component* component) {
    auto re=std::find(Comps.begin(),Comps.end(),component);
    if (re!=Comps.end()) {
        Comps.erase(re);
    }
}

Component* Entity::GetComponent(Component::Tag tag) {
    for (auto component:Comps) { // for loop die alleen werkt met begin en end dingen
        if (component->GetTag()==tag){
            return component;
        }

    }
    return nullptr; //component niet gevonden in vector met opgegeven tag
}

std::vector<Component::Tag>& Entity::GetTags() {
    vec_tags.clear();
    for (auto component:Comps) {
        vec_tags.push_back(component->GetTag());
    }
    return vec_tags;
}

std::vector<Component*>& Entity::GetComponents() {
    return Comps;
}

