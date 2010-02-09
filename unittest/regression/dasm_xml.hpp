#ifndef __REGRESION_DASM_XML_HPP__
#define __REGRESION_DASM_XML_HPP__

#include <iostream>
#include <beaengine/BeaEngine.h>
#include "unittest/regression/dasm_result.hpp"

void dasm_to_xml (std::ostream& os, const results_list_t& rl);
void dasm_to_sexp (std::ostream& os, const results_list_t& rl);


#endif
