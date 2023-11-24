#include <iostream>

int main() {
  for (auto c{' '}; c <= '~'; ++c) {
    std::cout << c << ' ';
  }
  std::cout << std::endl;
}
