#include "Entity.h"

#include "Component.h"

int Entity::nextSerial = 0;
std::set<Entity> Entity::entities;

Entity& Entity::createNewEntity() {
  auto entity = Entity{};
  auto pair = entities.insert(entity);
  auto& constRef = *pair.first;
  return const_cast<Entity&>(constRef);
}

void Entity::destroyEntity(const Entity& e) {
  for (auto* component : e.m_components) delete component;
  entities.erase(e);
}

bool Entity::hasAllOfTheseComponents(
    std::set<std::string> componentNames) const {
  for (auto* component : m_components) {
    const auto thisComponent = component->getClassID();
    componentNames.erase(thisComponent);
  }
  const auto allComponentsWereFound = componentNames.empty();
  return allComponentsWereFound;
}
