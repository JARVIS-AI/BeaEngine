set (target regression)

set (src main.cpp table_reader.cpp dasm_sexp.cpp Timer.cpp dasm_result.cpp temp_path.cpp zip_archive.cpp)
set (hdr table_reader.hpp dasm_sexp.hpp Timer.h dasm_result.hpp temp_path.hpp zip_archive.hpp)

add_executable (${target} ${src} ${hdr})

target_link_libraries (${target} microzip z ${BEA_TARGET})

if (NOT optBUILD_DLL)
  set_target_properties (${target} PROPERTIES COMPILE_FLAGS "-DBEA_ENGINE_STATIC") 
endif ()

