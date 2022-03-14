cmake_minimum_required(VERSION 2.8)

project(database_project_table)

include_directories(${SRC_CODE_DIR_})
include_directories(${SRC_INCLUDE_PATH_})

aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库
add_library(table_obj OBJECT ${DIR_LIB_SRCS})
add_dependencies(table_obj data_obj)
