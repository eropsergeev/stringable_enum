#include <iostream>
#include "stringable_enum.hpp"

ENUM(Color, RED = 1, GREEN, BLUE = 42, NONE = -1)

int main() {
    std::cout << to_string(Color::RED) << "\n";
    std::cout << to_string(Color::GREEN) << "\n";
    std::cout << to_string(Color::BLUE) << "\n";
}
