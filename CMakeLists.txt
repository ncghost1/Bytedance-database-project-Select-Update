cmake_minimum_required(VERSION 2.8)

project(database_project_main)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -pthread -lm -fPIC -ggdb3 -Og -lunwind -fno-omit-frame-pointer -no-pie -fno-strict-aliasing ${CMAKE_CXX_FLAGS}")

# path definition
set(THIRD_PARTY_DIR_ ${PROJECT_SOURCE_DIR}/thirdparty)
set(SRC_CODE_DIR_ ${PROJECT_SOURCE_DIR}/src)
set(SRC_INCLUDE_PATH_ ${PROJECT_SOURCE_DIR}/src/include)

# binary definition
# once the user pass the configure step, these binary libs should exist
set(gtest /usr/local/lib/libgtest.a)
set(gtest_main /usr/local/lib/libgtest_main.a)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# thirdparty code
add_subdirectory(thirdparty)

# source code
add_subdirectory(src)

# build test
add_subdirectory(test)
