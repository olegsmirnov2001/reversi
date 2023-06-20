#include "cell.h"

Cell inverse_color(Cell cell) {
  return static_cast<Cell>(static_cast<int8_t>(cell) ^ 1);
}
