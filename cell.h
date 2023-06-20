#pragma once
#include <cstdint>

enum Cell : int8_t { Black = 0, White = 1, Empty = 2 };

Cell inverse_color(Cell cell);
