set (sources
  unzip.c
  zip.c
  ioapi.c
  iowin32.c
)

set (headers
  unzip.h
  zip.h
  ioapi.h
  iowin32.h)

add_library (microzip STATIC ${sources} ${headers})

add_executable (u_zip minizip.c)
target_link_libraries (u_zip microzip z)

add_executable (u_unzip miniunz.c)
target_link_libraries (u_unzip microzip z)

