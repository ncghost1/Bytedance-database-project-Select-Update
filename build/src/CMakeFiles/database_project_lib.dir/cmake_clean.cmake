file(REMOVE_RECURSE
  "libdatabase_project_lib.pdb"
  "libdatabase_project_lib.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/database_project_lib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
