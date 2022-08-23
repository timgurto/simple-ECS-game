#include <conio.h>

#include <iostream>

auto playerLoc = 5;
auto mapSize = 10;

void handleInput() {
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

  for (auto x = 1; x < playerLoc; ++x) std::cout << '.';
  std::cout << 'P';
  for (auto x = playerLoc + 1; x != mapSize; ++x) std::cout << '.';

  std::cout << std::flush;
}

int main() {
  while (true) {
    drawGameState();
    handleInput();
  }
}
