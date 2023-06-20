cmake_minimum_required(VERSION 3.12)
project(Reversi)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic -Wold-style-cast -ffast-math")
add_executable(main main.cpp)

add_library(reversi STATIC cell.h cell.cpp reversi.h reversi.cpp main.cpp)
target_include_directories(reversi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(main PRIVATE reversi)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(reversi_test test/reversi.cpp)
target_link_libraries(reversi_test ${GTEST_BOTH_LIBRARIES} reversi)
