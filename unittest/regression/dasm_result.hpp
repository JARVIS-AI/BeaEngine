#ifndef __DASM_RESULT_HPP__
#define __DASM_RESULT_HPP__

#include <list>
#include <string>
#include <beaengine/BeaEngine.h>
#include "unittest/regression/table_reader.hpp"

struct dasm_result_entry_s
{
  dasm_result_entry_s ();
  dasm_result_entry_s (DISASM* dasm, const table_item_c& ti, int dasm_len);
  dasm_result_entry_s (const dasm_result_entry_s& obj);
  ~dasm_result_entry_s ();

  
  DISASM*            m_dasm;
  table_item_c       m_input;
  const int          m_dasm_len;
};

class dasm_result_c
{
public:
  typedef std::list <dasm_result_entry_s> results_list_t;
  typedef results_list_t::const_iterator  iterator_t;
public:
  dasm_result_c (const char* name, const char* comment);
  ~dasm_result_c ();
  void add (DISASM* dasm, const table_item_c& ti, int dasm_len, 
	    double microsecs);

  std::string name () const;
  std::string comment () const;

  size_t size () const;
  double total_time () const; // in microsecs
  double avg_time   () const; // in microsecs

  iterator_t begin () const;
  iterator_t end   () const;
private:
  std::string    m_name;
  std::string    m_comment;
  double         m_time;
  results_list_t m_list;
};

#endif
