C++17 stringable enum
===================
Small library that lets create enums that automatically convertable to string.

Examples:
```c++
#include "stringable_enum.hpp"

ENUM_CLASS(Color, RED = 1, GREEN, BLUE = 42, NONE = -1) // declare enum class "Color" and function "to_string"

// Or simple enum:
// ENUM(Color, RED = 1, GREEN, BLUE = 42, NONE = -1)

std::cout << to_string(Color::RED) << "\n"; // Output: RED
```

Only integer constants allowed for values:
```c++
ENUM(Invalid, A = 2 + 2, B = 5) // Works, but to_string can return any option or empty string.
```
