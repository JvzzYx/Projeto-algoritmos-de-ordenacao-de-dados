#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "faker-cxx::faker-cxx" for configuration "Debug"
set_property(TARGET faker-cxx::faker-cxx APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(faker-cxx::faker-cxx PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libfaker-cxx.a"
  )

list(APPEND _cmake_import_check_targets faker-cxx::faker-cxx )
list(APPEND _cmake_import_check_files_for_faker-cxx::faker-cxx "${_IMPORT_PREFIX}/lib/libfaker-cxx.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
