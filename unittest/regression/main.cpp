#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <list>
#include <string.h>

#include <beaengine/BeaEngine.h>

#include "unittest/regression/table_reader.hpp"
#include "unittest/regression/dasm_xml.hpp"
#include "unittest/regression/Timer.h"

struct dasm_result_s
{
  dasm_result_s ()
    : m_dasm     (0),
      m_dasm_len (-1)
  {
  }
  
  dasm_result_s (DISASM* dasm, const table_item_c& ti, int dasm_len)
    : m_dasm     (dasm),
      m_input    (ti),
      m_dasm_len (dasm_len)
  {
  }

  ~dasm_result_s ()
  {
    if (m_dasm)
      {
	delete m_dasm;
      }
  }
  
  DISASM*            m_dasm;
  table_item_c       m_input;
  const int          m_dasm_len;
};

typedef std::list <dasm_result_s> results_list_t;

// ===================================================================
void do_disasm_test (const char* table_file, results_list_t& results)
{
  std::cout << "Loading table from " << table_file << std::endl;
  table_reader_c reader (table_file);
  std::cout << "Table loaded. Number of entries: " 
	    << reader.items () << std::endl;
  double total_time = 0.0;
  for (size_t i=0; i<reader.items (); i++)
    {
      const table_item_c& ti = reader.at (i);
      DISASM* dasm = new DISASM;
      memset (dasm, 0, sizeof(DISASM));
      dasm->EIP = (UIntPtr) ti.bytes ();
      Timer timer;
      timer.start ();
      int len = Disasm (dasm);
      timer.stop ();
      double e = timer.getElapsedTimeInMicroSec ();
      total_time = total_time + e;
      results.push_back (dasm_result_s (dasm, ti, len));
    }
  double items = reader.items ();
  std::cout << "Total disassembly time: " << total_time << " micro-secs" << std::endl
	    << "Avg. disassembly time: " << total_time / items << std::endl;
}
// ----------------------------------------------------------
int main (int argc, char* argv [])
{
  if (argc != 2)
    {
      std::cerr << "USAGE: " << argv [0] << " <table file name>" << std::endl;
      return 1;
    }
  const char* table_file = argv [1];
  try
    {
      results_list_t dasm_results;
      do_disasm_test (table_file, dasm_results);
      return 0;
    }
  catch (std::exception& e)
    {
      std::cerr << "Error: " << e.what () << std::endl;
    }
  return 1;
}
