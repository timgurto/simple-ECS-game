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

void drawGameState() {
  std::cout << '\r';

  auto map = std::string(mapSize, '.');
  map[gPlayerLoc] = 'P';
  std::cout << map;

  std::cout << std::flush;
}

int main() {
  // 1. Set up systems and their related components
  auto &drawingSystem = System::createNewSystem();
  drawingSystem.requires<Drawable>();
  drawingSystem.requires<HasLocation>();
  drawingSystem.setUpdateFunction([](Entity &entity) { ; });

  // 2. Set up entities
  auto &player = Entity::createNewEntity();
  player.addComponent<Drawable>().glyph = 'p';
  player.addComponent<HasLocation>().linkedGlobal = &gPlayerLoc;

  while (true) {
    drawingSystem.update();
    drawGameState();
    handleNextKeyPress();
  }

  Entity::destroyEntity(player);
}
