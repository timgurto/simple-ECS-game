#pragma once

#include <set>
#include <vector>

class Entity;
struct Component;

class System {
 public:
  using Entities = std::set<Entity *>;

  using UpdateFunction = void (*)(Entities &relevantEntities);

  static System &createNewSystem();

  void update();

  template <typename COMPONENT>
  System &requiresComponent() {
    m_requiredComponents.insert(COMPONENT::classID);
    return *this;
  }

  System &setUpdateFunction(UpdateFunction func);

  static void registerEntityWithRelevantSystems(const Component &component,
                                                Entity &entity);

 private:
  Entities m_relevantEntities;
  UpdateFunction m_updateFunction{nullptr};

  // For an Entity to be 'relevant', it must have all of these components
  std::set<std::string> m_requiredComponents;

  static std::vector<System> registeredSystems;
};
