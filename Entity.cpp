#include "Entity.h"



void Entity::Add(Component* component) {
    vec_comps.push_back(component);
    vec_tags.push_back(component->GetTag());
}

void Entity::Remove(Component* component) {
    std::vector<Component*>::iterator re=std::find(vec_comps.begin(),vec_comps.end(),component);
    if (re!=vec_comps.end()) {
        vec_comps.erase(re);
        std::vector<Component::Tag>::iterator re2=std::find(vec_tags.begin(),vec_tags.end(),component->GetTag());
        vec_tags.erase(re2);
    }
}

Component* Entity::GetComponent(Component::Tag tag) {
    for (Component* component:vec_comps) { 
        if (component->GetTag()==tag){
            return component;
        }
    }
    return nullptr; 
}

std::vector<Component::Tag>& Entity::GetTags() {
    return vec_tags;
}

std::vector<Component*>& Entity::GetComponents() {
    return vec_comps;
}

