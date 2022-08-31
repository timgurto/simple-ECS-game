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

int main() {
  // 1. Set up systems and their related components
  auto &drawingSystem =
      System::createNewSystem()
          .requiresComponent<Drawable>()
          .requiresComponent<HasLocation>()
          .setUpdateFunction([](System::Entities &relevantEntities) {
            // Clear
            std::cout << '\r';
            auto map = std::string(mapSize, ' ');

            // Draw entities (in two passes)
            for (auto *entity : relevantEntities) {
              const auto &drawable = entity->getComponent<Drawable>();
              if (!drawable.shouldDrawBehind) continue;
              auto location = entity->getComponent<HasLocation>().getLocation();
              map[location] = drawable.glyph;
            }
            for (auto *entity : relevantEntities) {
              const auto &drawable = entity->getComponent<Drawable>();
              if (drawable.shouldDrawBehind) continue;
              auto location = entity->getComponent<HasLocation>().getLocation();
              map[location] = drawable.glyph;
            }

            // Present
            std::cout << map;
            std::cout << std::flush;
          });

  // 2. Set up entities
  const auto mapSize = 10;
  for (auto i = 0; i != mapSize; ++i) {
    auto &mapCell = Entity::createNewEntity();
    mapCell.addComponent<Drawable>().drawBehind().glyph = '.';
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
    drawingSystem.update();
    handleNextKeyPress();
  }
}
