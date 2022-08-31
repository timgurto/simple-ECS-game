#pragma once

#include <set>

#include "System.h"

struct Component;

class Entity {
 public:
  static Entity& createNewEntity();

  static void destroyEntity(const Entity& e);

  bool operator<(const Entity& rhs) const;

  template <typename COMPONENT>
  COMPONENT& addComponent() {
    auto* component = new COMPONENT;
    m_components.insert(component);
    System::registerEntityWithRelevantSystems(*component, *this);
    return *component;
  }

  template <typename DESIRED_COMPONENT>
  DESIRED_COMPONENT& getComponent() {
    for (auto* component : m_components) {
      if (component->getClassID() == DESIRED_COMPONENT::classID)
        return dynamic_cast<DESIRED_COMPONENT&>(*component);
    }

    // Assumption: execution will never get here
    return *new DESIRED_COMPONENT;
  }

  bool hasAllOfTheseComponents(std::set<std::string> componentNames) const;

 private:
  Entity();

  int m_serial;
  std::set<Component*> m_components;
  static int nextSerial;

  static std::set<Entity> entities;
};
