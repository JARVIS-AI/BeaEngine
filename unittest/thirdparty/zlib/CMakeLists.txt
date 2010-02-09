set (zlib_sources
adler32.c   crc32.c    gzio.c      infcodes.c  inflate.c   infutil.c  uncompr.c
compress.c  deflate.c  infblock.c  inffast.c   inftrees.c  trees.c    zutil.c
)

set (zlib_headers
deflate.h   infcodes.h  inffixed.h  infutil.h  zconf.h  zutil.h
infblock.h  inffast.h   inftrees.h  trees.h    zlib.h
)


add_library (z STATIC ${zlib_sources} ${zlib_headers})

