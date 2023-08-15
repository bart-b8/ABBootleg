#include "Engine.h"


void Engine::AddEntity(Entity* entity) {
    vec_entitys.push_back(entity);
    UpdateEntity(entity, entity->GetTags(), false);
}

void Engine::UpdateEntity(Entity* entity, std::vector<Component::Tag>& tags, bool remove) {
    entityStream->EntityUpdated(entity, tags, remove);
}

std::vector<Entity*>::iterator Engine::RemoveEntity(Entity* entity) {
    std::vector<Entity*>::iterator re=std::find(vec_entitys.begin(),vec_entitys.end(),entity);
    if (re!=vec_entitys.end()){
        re=vec_entitys.erase(re); // check
        UpdateEntity(entity, entity->GetTags(), true);
    }
    return re;
}

void Engine::AddSystem(System* system) {
    vec_systems.push_back(system);
    system->SetEngine(this);
}

std::vector<System*>::iterator Engine::RemoveSystem(System* system) {
    std::vector<System*>::iterator re=std::find(vec_systems.begin(),vec_systems.end(),system);
    if (re!=vec_systems.end()){
        re=vec_systems.erase(re); //check
    }
    return re;
}

std::vector<Entity*>& Engine::GetEntities() {
    return vec_entitys;
}

void Engine::Update() {
     for (System* system:vec_systems){
        system->Update();
     }
}

EntityStream& Engine::GetEntityStream() {
    return *entityStream;
}

Context& Engine::GetContext() {
    return context_;
}
