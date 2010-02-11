if (NOT ZLIB_FOUND)
  add_subdirectory (thirdparty/zlib)
endif ()

add_subdirectory (thirdparty/sexpr)
add_subdirectory (thirdparty/microzip)
add_subdirectory (regression)