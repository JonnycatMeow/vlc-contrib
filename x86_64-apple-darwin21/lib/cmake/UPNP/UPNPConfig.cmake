
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was UPNP.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

INCLUDE (CMakeFindDependencyMacro)
CHECK_REQUIRED_COMPONENTS (UPNP)
FIND_DEPENDENCY (IXML 1.14.15)
INCLUDE (${CMAKE_CURRENT_LIST_DIR}/UPNP.cmake)

SET (UPNP_ENABLE_BLOCKING_TCP_CONNECTIONS OFF CACHE INTERNAL "see.upnpconfig.h")
SET (UPNP_ENABLE_IPV6 ON CACHE INTERNAL "see.upnpconfig.h")
SET (UPNP_ENABLE_OPEN_SSL OFF CACHE INTERNAL "see.upnpconfig.h")
SET (UPNP_ENABLE_POST_WRITE  CACHE INTERNAL "see.upnpconfig.h")
SET (UPNP_ENABLE_UNSPECIFIED_SERVER OFF CACHE INTERNAL "see.upnpconfig.h")
SET (UPNP_HAVE_CLIENT ON CACHE INTERNAL "see.upnpconfig.h")
SET (UPNP_HAVE_DEVICE ON CACHE INTERNAL "see.upnpconfig.h")
SET (UPNP_HAVE_GENA ON CACHE INTERNAL "see.upnpconfig.h")
SET (UPNP_HAVE_OPTSSDP ON CACHE INTERNAL "see.upnpconfig.h")
SET (UPNP_HAVE_SOAP ON CACHE INTERNAL "see.upnpconfig.h")
SET (UPNP_HAVE_SSDP ON CACHE INTERNAL "see.upnpconfig.h")
SET (UPNP_HAVE_TOOLS ON CACHE INTERNAL "see.upnpconfig.h")
SET (UPNP_HAVE_WEBSERVER ON CACHE INTERNAL "see.upnpconfig.h")
SET (UPNP_LARGEFILE_SENSITIVE FALSE CACHE INTERNAL "see.upnpconfig.h")
SET (UPNP_MINISERVER_REUSEADDR ON CACHE INTERNAL "see.upnpconfig.h")
