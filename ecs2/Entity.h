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

  bool hasAllOfTheseComponents(std::set<std::string> componentNames) const;

 private:
  Entity();

  int m_serial;
  std::set<Component*> m_components;
  static int nextSerial;

  static std::set<Entity> entities;
};
