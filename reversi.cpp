#include "reversi.h"

std::ostream& operator<<(std::ostream& stream, const ReversiSimulator& reversi_simulator) {
  assert(reversi_simulator.columns_ <= 26 && reversi_simulator.rows_ <= 9);
  auto draw_horizontal_boundary = [&]() {
    stream << "  +-";
    for (size_t column = 0; column < reversi_simulator.columns_; ++column) {
      stream << "--";
    }
    stream << "+\n";
  };
  draw_horizontal_boundary();
  for (size_t row = 0; row < reversi_simulator.rows_; ++row) {
    stream << (row + 1) << " | ";
    for (size_t column = 0; column < reversi_simulator.columns_; ++column) {
      switch (reversi_simulator.field_[row][column]) {
        case Cell::Empty:
          stream << " ";
          break;
        case Cell::Black:
          stream << "●";
          break;
        case Cell::White:
          stream << "○";
          break;
      }
      stream << " ";
    }
    stream << "|\n";
  }
  draw_horizontal_boundary();
  stream << "   ";
  for (size_t column = 0; column < reversi_simulator.columns_; ++column) {
    stream << " " << static_cast<char>('A' + column);
  }
  stream << "\n";
  return stream;
}
