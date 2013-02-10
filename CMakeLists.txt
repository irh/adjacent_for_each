cmake_minimum_required(VERSION 2.6)
project(boost_adjacent_for_each)

include_directories(.)

add_executable(adjacent_for_each_example libs/algorithm/example/adjacent_for_each_example.cpp)
add_executable(adjacent_for_each_test libs/algorithm/test/adjacent_for_each_test.cpp)

ENABLE_TESTING()
ADD_TEST(adjacent_for_each_test ${CMAKE_CURRENT_BINARY_DIR}/adjacent_for_each_test)
