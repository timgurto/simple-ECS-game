#include <conio.h>

#include <iostream>
#include <string>

auto playerLoc = 5;
auto mapSize = 10;

void handleNextKeyPress() {
  const auto LEFT_ARROW = 75;
  const auto RIGHT_ARROW = 77;

  switch (_getch()) {
    case LEFT_ARROW:
      --playerLoc;
      break;

    case RIGHT_ARROW:
      ++playerLoc;
      break;
  }
}

void drawGameState() {
  std::cout << '\r';

  auto map = std::string(mapSize, '.');
  map[playerLoc] = 'P';
  std::cout << map;

  std::cout << std::flush;
}

int main() {
  while (true) {
    drawGameState();
    handleNextKeyPress();
  }
}
