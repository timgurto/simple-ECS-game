#include "System.h"

#include "Entity.h"

std::vector<System> System::registeredSystems;

void System::onComponentAddedToEntity(const Component &component,
                                      Entity &entity) {
  for (auto &system : registeredSystems)
    if (entity.hasAllOfTheseComponents(system.m_requiredComponents))
      system.m_relevantEntities.insert(&entity);
}
