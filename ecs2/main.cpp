#include <conio.h>

#include <iostream>

int main() {
  while (true) {
    auto c = _getch();
    std::cout << '\r' << c << std::flush;
  }
}
