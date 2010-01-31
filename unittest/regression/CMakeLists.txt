set (target regression)

set (src regression.c table_reader.cpp)
set (hdr table_reader.hpp)

add_executable (${target} ${src} ${hdr})

target_link_libraries (${target} ${BEA_TARGET})

if (NOT optBUILD_DLL)
	set_target_properties (${target} PROPERTIES COMPILE_FLAGS "-DBEA_ENGINE_STATIC") 
endif ()

