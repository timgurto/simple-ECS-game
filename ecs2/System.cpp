#include "System.h"

#include "Entity.h"

std::vector<System> System::registeredSystems;

System &System::createNewSystem() {
  registeredSystems.push_back({});
  return registeredSystems.back();
}

void System::registerEntityWithRelevantSystems(const Component &component,
                                               Entity &entity) {
  for (auto &system : registeredSystems)
    if (entity.hasAllOfTheseComponents(system.m_requiredComponents))
      system.m_relevantEntities.insert(&entity);
}

System &System::setUpdateFunction(UpdateFunction func) {
  m_updateFunction = func;
  return *this;
}

void System::update(void *data) {
  if (!m_updateFunction) return;

  for (auto *entity : m_relevantEntities) m_updateFunction(*entity, data);
}
