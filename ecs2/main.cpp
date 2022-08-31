#include <conio.h>

#include <iostream>
#include <string>

#include "Component.h"
#include "Entity.h"
#include "System.h"

auto gPlayerLoc = 5;
auto mapSize = 10;

void handleNextKeyPress() {
  const auto LEFT_ARROW = 75;
  const auto RIGHT_ARROW = 77;

  switch (_getch()) {
    case LEFT_ARROW:
      --gPlayerLoc;
      break;

    case RIGHT_ARROW:
      ++gPlayerLoc;
      break;
  }
}

void drawGameState(System &drawingSystem) {
  std::cout << '\r';

  auto map = std::string(mapSize, '.');
  drawingSystem.update(&map);  // Draw all drawable entities
  std::cout << map;

  std::cout << std::flush;
}

int main() {
  // 1. Set up systems and their related components
  auto &drawingSystem =
      System::createNewSystem()
          .requiresComponent<Drawable>()
          .requiresComponent<HasLocation>()
          .setUpdateFunction([](Entity &entity, void *data) {
            auto &map = *reinterpret_cast<std::string *>(data);
            auto location = *entity.getComponent<HasLocation>().linkedGlobal;
            auto glyph = entity.getComponent<Drawable>().glyph;
            map[location] = glyph;
          });

  // 2. Set up entities
  auto &player = Entity::createNewEntity();
  player.addComponent<Drawable>().glyph = 'P';
  player.addComponent<HasLocation>().linkedGlobal = &gPlayerLoc;

  while (true) {
    drawGameState(drawingSystem);
    handleNextKeyPress();
  }

  Entity::destroyEntity(player);
}
