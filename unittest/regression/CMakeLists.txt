set (target regression)
set (src ${target}.c)
add_executable (${target} ${src})
target_link_libraries (${target} ${BEA_TARGET})
if (NOT optBUILD_DLL)
	set_target_properties (${target} PROPERTIES COMPILE_FLAGS "-DBEA_ENGINE_STATIC") 
endif ()

