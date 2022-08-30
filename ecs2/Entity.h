#pragma once

#include <set>

struct Component;

class Entity {
 public:
  static Entity& createNewEntity() {
    auto entity = Entity{};
    auto pair = entities.insert(entity);
    auto& constRef = *pair.first;
    return const_cast<Entity&>(constRef);
  }

  static void destroyEntity(const Entity& e) {
    for (auto* component : e.m_components) delete component;
    entities.erase(e);
  }

  bool operator<(const Entity& rhs) const { return m_serial < rhs.m_serial; }

  template <typename C>
  void addComponent(C* c) {
    m_components.insert(c);
  }

 private:
  Entity() : m_serial(nextSerial++) {}

  int m_serial;
  std::set<Component*> m_components;
  static int nextSerial;

  static std::set<Entity> entities;
};

int Entity::nextSerial = 0;
std::set<Entity> Entity::entities;
