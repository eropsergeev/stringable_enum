#include <iostream>
#include "stringable_enum.hpp"

namespace A {
    ENUM_CLASS(Color, int, RED = 1, GREEN, BLUE = 42, NONE = -1)
    ENUM_CLASS(Foo, int, BAR, BAZ)
};

int main() {
    using namespace A::stringable_enum;
    std::cout << to_string(A::Color::RED) << "\n";
    std::cout << to_string(A::Color::GREEN) << "\n";
    std::cout << to_string(A::Color::BLUE) << "\n";
    for (auto x : EnumValues<A::Color>::list) {
        std::cout << to_string(x) << " ";
    }
    std::cout << "\n";
}
