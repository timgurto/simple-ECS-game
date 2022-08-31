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

void System::update() {
  if (m_updateFunction) m_updateFunction(m_relevantEntities);
}
