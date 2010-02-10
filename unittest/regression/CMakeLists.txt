set (target regression)

set (src main.cpp table_reader.cpp dasm_xml.cpp Timer.cpp dasm_result.cpp)
set (hdr table_reader.hpp dasm_xml.hpp Timer.h dasm_result.hpp)

add_executable (${target} ${src} ${hdr})

target_link_libraries (${target} z ${BEA_TARGET})

if (NOT optBUILD_DLL)
  set_target_properties (${target} PROPERTIES COMPILE_FLAGS "-DBEA_ENGINE_STATIC") 
endif ()

