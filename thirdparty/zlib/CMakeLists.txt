set (zlib_sources
adler32.c   crc32.c    gzio.c      infcodes.c  inflate.c   infutil.c  uncompr.c
compress.c  deflate.c  infblock.c  inffast.c   inftrees.c  trees.c    zutil.c
)

set (zlib_headers
deflate.h   infcodes.h  inffixed.h  infutil.h  zconf.h  zutil.h
infblock.h  inffast.h   inftrees.h  trees.h    zlib.h
)

if (optBUILD_DLL)
  add_library (z SHARED ${zlib_sources} ${zlib_headers})
else ()
  add_library (z STATIC ${zlib_sources} ${zlib_headers})
endif ()

if (optBUILD_DLL)
  set ( ZLIB_DEFS "-DZLIB_DLL")
endif ()

if (ZLIB_DEFS)
  set_target_properties (z PROPERTIES COMPILE_FLAGS ${ZLIB_DEFS}) 
endif ()

add_executable (zpipe zpipe.c)
target_link_libraries (zpipe z)