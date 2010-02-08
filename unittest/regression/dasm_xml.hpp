#ifndef __REGRESION_DASM_XML_HPP__
#define __REGRESION_DASM_XML_HPP__

#include <iostream>
#include <beaengine/BeaEngine.h>
#include "unittest/regression/table_reader.hpp"

void dasm_to_xml (std::ostream& os, const DISASM& dasm, int dasm_len, const table_item_c& expected);


#endif
