set (sources 
  cstring.c     faststack.c  parser.c  sexp_memory.c  sexp_vis.c
  event_temp.c  io.c         sexp.c    sexp_ops.c
)

set (headers 
cstring.h    sexp.h         sexp_memory.h  sexp_vis.h
faststack.h  sexp_errors.h  sexp_ops.h
)

add_library (sexpr STATIC ${sources} ${headers})

if (BEA_COMPILER STREQUAL gnu)
set_target_properties (sexpr PROPERTIES COMPILE_FLAGS "-w")
endif ()
