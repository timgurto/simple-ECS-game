#pragma once

#include <set>
#include <vector>

class Entity;
struct Component;

class System {
 public:
  using UpdateFunction = void (*)(Entity &);

  static System &createNewSystem() {
    registeredSystems.push_back({});
    return registeredSystems.back();
  }

  virtual void update() {
    if (!m_updateFunction) return;

    for (auto *entity : m_relevantEntities) m_updateFunction(*entity);
  }

  template <typename COMPONENT>
  void requires() {
    m_requiredComponents.insert(COMPONENT::classID);
  }

  void setUpdateFunction(UpdateFunction func) { m_updateFunction = func; }

  static void registerEntityWithRelevantSystems(const Component &component,
                                                Entity &entity);

 private:
  std::set<Entity *> m_relevantEntities;
  UpdateFunction m_updateFunction{nullptr};

  // For an Entity to be 'relevant', it must have all of these components
  std::set<std::string> m_requiredComponents;

  static std::vector<System> registeredSystems;
};
