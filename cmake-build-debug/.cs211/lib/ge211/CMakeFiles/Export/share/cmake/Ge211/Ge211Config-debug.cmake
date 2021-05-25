#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ge211" for configuration "Debug"
set_property(TARGET ge211 APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(ge211 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libge211.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS ge211 )
list(APPEND _IMPORT_CHECK_FILES_FOR_ge211 "${_IMPORT_PREFIX}/lib/libge211.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
