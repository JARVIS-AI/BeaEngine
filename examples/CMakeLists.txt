set (examples 
			basic security_block virtual_address options stack_movs control_flow
			data_flow_eax  data_flow_mod_mem
	)

foreach (target ${examples})
	set (src ${target}.c)
	add_executable (${target} ${src})
	target_link_libraries (${target} ${BEA_TARGET})
endforeach ()
