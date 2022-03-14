cmake_minimum_required(VERSION 2.8)

project(database_project_test_lab1)

file(GLOB LAB_1_TEST_SRCS "*_test.cc")

foreach(TEST_FILE ${LAB_1_TEST_SRCS})
  build_test(${TEST_FILE} database_project_lib)
endforeach()
