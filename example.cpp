#include <iostream>
#include "stringable_enum.hpp"

namespace A {
    ENUM(Color, int, RED = 1, GREEN, BLUE = 42, NONE = -1)
};

int main() {
    using namespace A::stringable_enum;
    std::cout << to_string(A::Color::RED) << "\n";
    std::cout << to_string(A::Color::GREEN) << "\n";
    std::cout << to_string(A::Color::BLUE) << "\n";
    for (auto x : enum_values<A::Color>) {
        std::cout << to_string(static_cast<A::Color>(x)) << " ";
    }
    std::cout << "\n";
}
