#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "UPNP::Static" for configuration "RelWithDebInfo"
set_property(TARGET UPNP::Static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(UPNP::Static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libupnp.a"
  )

list(APPEND _cmake_import_check_targets UPNP::Static )
list(APPEND _cmake_import_check_files_for_UPNP::Static "${_IMPORT_PREFIX}/lib/libupnp.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
