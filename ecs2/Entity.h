#pragma once

#include <set>

#include "System.h"

class Component;

class Entity {
 public:
  static Entity& createNewEntity();

  static void destroyEntity(const Entity& e);

  bool operator<(const Entity& rhs) const { return m_serial < rhs.m_serial; }

  template <typename C>
  void addComponent(C* c) {
    m_components.insert(c);
    System::registerEntityWithRelevantSystems(*c, *this);
  }

  bool hasAllOfTheseComponents(std::set<std::string> componentNames) const;

 private:
  Entity() : m_serial(nextSerial++) {}

  int m_serial;
  std::set<Component*> m_components;
  static int nextSerial;

  static std::set<Entity> entities;
};
