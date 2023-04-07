#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "umock_c" for configuration "Debug"
set_property(TARGET umock_c APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(umock_c PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "azure_macro_utils_c"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/umock_c.lib"
  )

list(APPEND _cmake_import_check_targets umock_c )
list(APPEND _cmake_import_check_files_for_umock_c "${_IMPORT_PREFIX}/debug/lib/umock_c.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
