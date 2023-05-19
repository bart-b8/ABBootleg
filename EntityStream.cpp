#include "EntityStream.h"


std::set<Entity*> EntityStream::WithTag(Component::Tag tag) {
    if (map_entitys.count(tag)>0){
        return map_entitys[tag];
    }
    return std::set<Entity*>(); //check
}

std::set<Entity*> EntityStream::WithTags(std::set<Component::Tag>& tags) {
    std::set<Entity*> temp_entitys;
    if (!tags.empty()) {
        auto it = map_entitys.find(*tags.begin());
        if (it != map_entitys.end()) {
            temp_entitys = it->second;
            tags.erase(tags.begin());
            for (const auto& tag : tags) {
                auto it = map_entitys.find(tag);
                if (it != map_entitys.end()) {
                    std::set<Entity*> intersection;
                    std::set_intersection(temp_entitys.begin(), temp_entitys.end(), it->second.begin(), it->second.end(),
                        std::inserter(intersection, intersection.begin()));
                    temp_entitys = intersection;
                } else {
                    temp_entitys.clear();
                    break;
                }
            }
        }
    }
    return temp_entitys;
}


void EntityStream::EntityUpdated(Entity* entity, std::vector<Component::Tag>& tags, bool remove) {
     for (const auto& tag : tags) {
        if (remove) {
            map_entitys[tag].erase(entity);
        } else {
            map_entitys[tag].insert(entity);//check
        }
    }
}

