cmake_minimum_required(VERSION 2.8)

project(database_project_data)

include_directories(${THIRD_PARTY_DIR_})
include_directories(${SRC_INCLUDE_PATH_})

aux_source_directory(. DIR_LIB_SRCS)

add_library(data_obj OBJECT ${DIR_LIB_SRCS})
