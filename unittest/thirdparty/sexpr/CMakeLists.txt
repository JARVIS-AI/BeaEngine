set (sources 
  cstring.c     faststack.c  parser.c  sexp_memory.c  sexp_vis.c
  event_temp.c  io.c         sexp.c    sexp_ops.c
)

set (headers 
cstring.h    sexp.h         sexp_memory.h  sexp_vis.h
faststack.h  sexp_errors.h  sexp_ops.h
)

add_library (sexpr STATIC ${sources} ${headers})
add_executable (sexp_demo sexp_demo/main.cpp)
target_link_libraries (sexp_demo sexpr)


