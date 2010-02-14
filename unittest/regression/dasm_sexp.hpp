#ifndef __REGRESION_DASM_SEXP_HPP__
#define __REGRESION_DASM_SEXP_HPP__

#include <iostream>
#include <beaengine/BeaEngine.h>
#include "unittest/regression/dasm_result.hpp"

void dasm_to_sexp (std::ostream& os, const dasm_result_c& rl);

#endif
