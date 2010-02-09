#ifndef __DASM_RESULT_HPP__
#define __DASM_RESULT_HPP__

#include <list>
#include <beaengine/BeaEngine.h>
#include "unittest/regression/table_reader.hpp"

struct dasm_result_s
{
  dasm_result_s ();
  dasm_result_s (DISASM* dasm, const table_item_c& ti, int dasm_len);
  dasm_result_s (const dasm_result_s& obj);
  ~dasm_result_s ();

  
  DISASM*            m_dasm;
  table_item_c       m_input;
  const int          m_dasm_len;
};

typedef std::list <dasm_result_s> results_list_t;


#endif
