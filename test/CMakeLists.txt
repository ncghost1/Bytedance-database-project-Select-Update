cmake_minimum_required(VERSION 2.8)

project(database_project_test)

set(BUILD_LAB_1_UT false CACHE BOOL false)
set(BUILD_LAB_2_UT false CACHE BOOL false)

# define unit test function
function(build_test test_file)
  set(test_args ${ARGN})
  include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})
  include_directories(${SRC_CODE_DIR_})
  include_directories(${SRC_INCLUDE_PATH_})
  get_filename_component(test_target_name ${test_file} NAME_WE)
  add_executable(${test_target_name} ${test_file})
  target_link_libraries(${test_target_name} ${gtest_main} ${gtest} ${test_args})
  add_test(database_project_${test_target_name} ${test_target_name})
endfunction(build_test)

if (${BUILD_LAB_1_UT})
  add_subdirectory(lab1)
endif()

if (${BUILD_LAB_2_UT})
  add_subdirectory(lab2)
endif()
