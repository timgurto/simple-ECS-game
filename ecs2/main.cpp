#include <conio.h>

#include <iostream>
#include <string>

#include "Component.h"
#include "Entity.h"
#include "System.h"

const auto MAP_SIZE = 10;

const auto LEFT_ARROW = 75;
const auto RIGHT_ARROW = 77;

int main() {
  // 1. Set up systems and their related components
  auto &drawingSystem =
      System::createNewSystem()
          .requiresComponent<Drawable>()
          .requiresComponent<HasLocation>()
          .setUpdateFunction([](System::Entities &relevantEntities) {
            // Clear
            std::cout << '\r';
            auto map = std::string(MAP_SIZE, ' ');

            // Draw entities (in two passes)
            for (auto *entity : relevantEntities) {
              const auto &drawable = entity->getComponent<Drawable>();
              if (!drawable.shouldDrawBehind) continue;
              auto location = entity->getComponent<HasLocation>().location;
              map[location] = drawable.glyph;
            }
            for (auto *entity : relevantEntities) {
              const auto &drawable = entity->getComponent<Drawable>();
              if (drawable.shouldDrawBehind) continue;
              auto location = entity->getComponent<HasLocation>().location;
              map[location] = drawable.glyph;
            }

            // Present
            std::cout << map;
            std::cout << std::flush;
          });

  auto &keyboardSystem =
      System::createNewSystem()
          .requiresComponent<KeyboardControllable>()
          .requiresComponent<HasLocation>()
          .setUpdateFunction([](System::Entities &relevantEntities) {
            const auto nextKey = _getch();
            for (auto &entity : relevantEntities) {
              const auto &controls =
                  entity->getComponent<KeyboardControllable>();
              auto &location = entity->getComponent<HasLocation>().location;

              if (nextKey == controls.leftKey) --location;
              if (nextKey == controls.rightKey) ++location;
            }
          });

  // 2. Set up entities
  for (auto i = 0; i != MAP_SIZE; ++i) {
    auto &mapCell = Entity::createNewEntity();
    mapCell.addComponent<Drawable>().drawBehind().glyph = '.';
    mapCell.addComponent<HasLocation>().location = i;
  }

  auto &player = Entity::createNewEntity();
  player.addComponent<Drawable>().glyph = 'P';
  player.addComponent<HasLocation>().location = 2;
  player.addComponent<KeyboardControllable>()
      .setLeftKey(LEFT_ARROW)
      .setRightKey(RIGHT_ARROW);

  auto &monster = Entity::createNewEntity();
  monster.addComponent<Drawable>().glyph = 'M';
  monster.addComponent<HasLocation>().location = 8;

  // Start game loop
  while (true) {
    drawingSystem.update();
    keyboardSystem.update();
  }
}
