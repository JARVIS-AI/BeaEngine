#include <string.h>
#include "unittest/regression/dasm_result.hpp"

dasm_result_entry_s::dasm_result_entry_s ()
  : m_dasm     (0),
    m_dasm_len (-1)
{
}
// -------------------------------------------------------------  
dasm_result_entry_s::dasm_result_entry_s (DISASM* dasm, const table_item_c& ti, int dasm_len)
  : m_dasm     (0),
    m_input    (ti),
    m_dasm_len (dasm_len)
{
  m_dasm = new DISASM;
  memcpy (m_dasm, dasm, sizeof (DISASM));
}
// -------------------------------------------------------------  
dasm_result_entry_s::dasm_result_entry_s (const dasm_result_entry_s& obj)
  : m_input    (obj.m_input),
    m_dasm_len (obj.m_dasm_len)
{
  m_dasm = new DISASM;
  memcpy (m_dasm, obj.m_dasm, sizeof (DISASM));
}
// -------------------------------------------------------------     
dasm_result_entry_s::~dasm_result_entry_s ()
{
  if (m_dasm)
    {
      delete m_dasm;
    }
}
// =============================================================
dasm_result_c::dasm_result_c (const char* name, const char* comment)
  : m_name    (name),
    m_comment (comment),
    m_time    (0.0)
{
}
// -------------------------------------------------------------
dasm_result_c::~dasm_result_c ()
{
}
// -------------------------------------------------------------
void dasm_result_c::add (DISASM* dasm, 
			 const table_item_c& ti, 
			 int dasm_len, 
			 double microsecs)
{
  m_list.push_back (dasm_result_entry_s (dasm, ti, dasm_len));
  m_time = m_time + microsecs;
}
// -------------------------------------------------------------
size_t dasm_result_c::size () const
{
  return m_list.size ();
}
// -------------------------------------------------------------
double dasm_result_c::total_time () const
{
  return m_time;
}
// -------------------------------------------------------------
double dasm_result_c::avg_time   () const
{
  double s = (double)this->size ();
  return m_time / s;
}
// -------------------------------------------------------------
dasm_result_c::iterator_t dasm_result_c::begin () const
{
  return m_list.begin ();
}
// -------------------------------------------------------------
dasm_result_c::iterator_t dasm_result_c::end   () const
{
  return m_list.end ();
}
// -------------------------------------------------------------
std::string dasm_result_c::name () const
{
  return m_name;
}
// -------------------------------------------------------------
std::string dasm_result_c::comment () const
{
  return m_comment;
}
