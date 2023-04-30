#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "aribcaption::aribcaption" for configuration "RelWithDebInfo"
set_property(TARGET aribcaption::aribcaption APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(aribcaption::aribcaption PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C;CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libaribcaption.a"
  )

list(APPEND _cmake_import_check_targets aribcaption::aribcaption )
list(APPEND _cmake_import_check_files_for_aribcaption::aribcaption "${_IMPORT_PREFIX}/lib/libaribcaption.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
