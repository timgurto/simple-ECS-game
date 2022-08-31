#include <conio.h>

#include <iostream>
#include <string>

#include "Component.h"
#include "Entity.h"
#include "System.h"

auto gPlayerLoc = 2;
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

  auto map = std::string(mapSize, ' ');
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
            auto location = entity.getComponent<HasLocation>().getLocation();
            auto glyph = entity.getComponent<Drawable>().glyph;
            map[location] = glyph;
          });

  // 2. Set up entities
  const auto mapSize = 10;
  for (auto i = 0; i != mapSize; ++i) {
    auto &mapCell = Entity::createNewEntity();
    mapCell.addComponent<Drawable>().glyph = '.';
    mapCell.addComponent<HasLocation>().location = i;
  }

  auto &player = Entity::createNewEntity();
  player.addComponent<Drawable>().glyph = 'P';
  player.addComponent<HasLocation>().linkedGlobal = &gPlayerLoc;

  auto &monster = Entity::createNewEntity();
  monster.addComponent<Drawable>().glyph = 'M';
  monster.addComponent<HasLocation>().location = 8;

  // Start game loop
  while (true) {
    drawGameState(drawingSystem);
    handleNextKeyPress();
  }
}
