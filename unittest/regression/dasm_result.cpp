#include <string.h>
#include "unittest/regression/dasm_result.hpp"

dasm_result_s::dasm_result_s ()
  : m_dasm     (0),
    m_dasm_len (-1)
{
}
  
dasm_result_s::dasm_result_s (DISASM* dasm, const table_item_c& ti, int dasm_len)
  : m_dasm     (0),
    m_input    (ti),
    m_dasm_len (dasm_len)
{
  m_dasm = new DISASM;
  memcpy (m_dasm, dasm, sizeof (DISASM));
}

dasm_result_s::dasm_result_s (const dasm_result_s& obj)
  : m_input    (obj.m_input),
    m_dasm_len (obj.m_dasm_len)
{
  m_dasm = new DISASM;
  memcpy (m_dasm, obj.m_dasm, sizeof (DISASM));
}
   
   
dasm_result_s::~dasm_result_s ()
{
  if (m_dasm)
    {
      delete m_dasm;
    }
}
