#include "reversi.h"
#include <cmath>
#include <iostream>
#include <string>

void play_in_terminal() {
  ReversiSimulator reversi_simulator(8, 8);
  reversi_simulator.initialize();
  for (size_t move_count = 0;; ++move_count) {
    std::cout << reversi_simulator;
    Cell current_cell = move_count % 2 ? Cell::White : Cell::Black;
    while (true) {
      std::cout << "Enter position to insert " << (current_cell == Cell::Black ? "●" : "○")
                << ". Press enter to finish: ";
      std::string command;
      std::getline(std::cin, command);
      if (command.empty()) {
        std::cout << "Thanks for playing!\n";
        return;
      }
      if (command.size() != 2 || !('A' <= command.front() && command.front() <= 'Z') ||
          !('1' <= command.back() && command.back() <= '9')) {
        std::cout << "Wrong format. Please enter the cell as A1.\n";
        continue;
      }
      auto row = static_cast<size_t>(command.back() - '1');
      auto column = static_cast<size_t>(command.front() - 'A');
      if (!reversi_simulator.perform_move(row, column, current_cell)) {
        std::cout << "Invalid move. Try again.\n";
        continue;
      }
      break;
    }
  }
}

int main() {
  play_in_terminal();
  return 0;
}
