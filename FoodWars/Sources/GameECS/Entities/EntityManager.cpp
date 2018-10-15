#include "../../../Headers/GameECS/Entities/EntityManager.h"
#include <typeinfo>

EntityManager::EntityManager() {
    _lowestUnassignedEntityId = -1;
}

EntityManager::~EntityManager() = default;

int EntityManager::createEntity() {
    return ++_lowestUnassignedEntityId;
}

int EntityManager::createEntity(Component components[], int size) {
    for(int i=0; i < size; i++){
        // kan momenteel niet, omdat de name van de components altijd component zou zijn. Om dit op te lossen zou
        // component een virtual functie getname ofzo moeten hebben welke in elk component wordt override
    }
    return ++_lowestUnassignedEntityId;
}


void EntityManager::removeEntity(int entityId) {
    for (auto &iterator : _componentsByClass) {
        std::string key = iterator.first;
        iterator.second.erase(entityId);
    }
}