#pragma once
#include "cell.h"
#include <array>
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>

class ReversiSimulator {
public:
  ReversiSimulator(size_t columns, size_t rows):
      columns_(columns), rows_(rows), field_(rows, std::vector<Cell>(columns, Cell::Empty)) {
  }

  void initialize() {
    assert(columns_ >= 2 && rows_ >= 2);
    size_t central_row = rows_ / 2 - 1;
    size_t central_column = columns_ / 2 - 1;
    for (size_t row_shift : {0, 1}) {
      for (size_t column_shift : {0, 1}) {
        field_[central_row + row_shift][central_column + column_shift] =
            (row_shift ^ column_shift) ? Cell::White : Cell::Black;
      }
    }
  }

  bool perform_move(size_t cell_row, size_t cell_column, Cell new_color) {
    if (cell_column >= columns_ || cell_row >= rows_) {
      return false;
    }
    if (field_[cell_row][cell_column] != Cell::Empty) {
      return false;
    }
    if (new_color != Cell::Black && new_color != Cell::White) {
      return false;
    }
    bool turn_happened = false;
    for (int32_t row_shift : {-1, 0, 1}) {
      for (int32_t column_shift : {-1, 0, 1}) {
        auto perform_shift = [&](int32_t step) {
          return std::pair{
              static_cast<int32_t>(cell_row) + step * row_shift,
              static_cast<int32_t>(cell_column) + step * column_shift};
        };
        if (row_shift == 0 && column_shift == 0) {
          continue;
        }
        for (int32_t distance_to_same = 1;; ++distance_to_same) {
          auto [row_same, column_same] = perform_shift(distance_to_same);
          if (!(0 <= row_same && row_same < static_cast<int32_t>(rows_) && 0 <= column_same &&
                column_same < static_cast<int32_t>(columns_))) {
            break;
          }
          Cell current_cell = field_[static_cast<size_t>(row_same)][static_cast<size_t>(column_same)];
          if (current_cell == inverse_color(new_color)) {
            continue;
          }
          if (current_cell == Cell::Empty || distance_to_same <= 1) {
            break;
          }
          if (distance_to_same >= 2) {
            turn_happened = true;
            for (int32_t step = 1; step < distance_to_same; ++step) {
              auto [row_inverse, column_inverse] = perform_shift(step);
              auto& cell_to_inverse = field_[static_cast<size_t>(row_inverse)][static_cast<size_t>(column_inverse)];
              assert(cell_to_inverse == inverse_color(new_color));
              cell_to_inverse = new_color;
            }
          }
          break;
        }
      }
    }
    if (!turn_happened) {
      return false;
    }
    field_[cell_row][cell_column] = new_color;
    return true;
  }

  friend std::ostream& operator<<(std::ostream& stream, const ReversiSimulator& reversi_simulator);

private:
  const size_t columns_, rows_;
  std::vector<std::vector<Cell>> field_;
};
