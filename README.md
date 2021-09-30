C++17 stringable enum
===================
Small library that lets create enums that automatically convertable to string.

Examples:
```c++
#include "stringable_enum.hpp"

namespace A {

ENUM_CLASS(Color, int, RED = 1, GREEN, BLUE = 42, NONE = -1) // declare enum class "Color" and function "to_string"

};

// Or simple enum:
// ENUM(Color, RED = 1, GREEN, BLUE = 42, NONE = -1)

std::cout << A::stringable_enum::to_string(A::Color::RED) << "\n"; // Output: RED

for (int x : A::stringable_enum::enum_values<A::Color>) { // std::array of all values as enum's base type 
    ...
}

```

Only integer constants allowed for values:
```c++
ENUM(Invalid, int, A = 2 + 2, B = 5) // Works, but to_string can return any option or empty string.
```
