cmake_minimum_required(VERSION 2.8)

project(database_project_src)

add_subdirectory(include)
add_subdirectory(data)
add_subdirectory(table)

add_library(database_project_lib SHARED
	    $<TARGET_OBJECTS:data_obj>
		$<TARGET_OBJECTS:table_obj>)
