#include "Entity.h"



void Entity::Add(Component* component) {
    vec_comps.push_back(component);
}

void Entity::Remove(Component* component) {
    auto re=std::find(vec_comps.begin(),vec_comps.end(),component);
    if (re!=vec_comps.end()) {
        vec_comps.erase(re);
    }
}

Component* Entity::GetComponent(Component::Tag tag) {
    for (auto component:vec_comps) { 
        if (component->GetTag()==tag){
            return component;
        }
    }
    return nullptr; 
}

std::vector<Component::Tag>& Entity::GetTags() {
    vec_tags.clear();
    for (auto component:vec_comps) {
        vec_tags.push_back(component->GetTag());
    }
    return vec_tags;
}

std::vector<Component*>& Entity::GetComponents() {
    return vec_comps;
}

