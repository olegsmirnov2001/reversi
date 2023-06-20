#include "../reversi.h"
#include "gtest/gtest.h"
#include <iostream>
#include <sstream>

TEST(TestReversi, TestEmpty) {
  ReversiSimulator simulator(4, 4);
  std::ostringstream stream;
  stream << simulator;
  std::string expected =
      "  +---------+\n"
      "1 |         |\n"
      "2 |         |\n"
      "3 |         |\n"
      "4 |         |\n"
      "  +---------+\n"
      "    A B C D\n";
  EXPECT_EQ(stream.str(), expected);
}

TEST(TestReversi, TestInitialize) {
  ReversiSimulator simulator(4, 4);
  simulator.initialize();
  std::ostringstream stream;
  stream << simulator;
  std::string expected =
      "  +---------+\n"
      "1 |         |\n"
      "2 |   ● ○   |\n"
      "3 |   ○ ●   |\n"
      "4 |         |\n"
      "  +---------+\n"
      "    A B C D\n";
  EXPECT_EQ(stream.str(), expected);
}
