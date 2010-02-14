#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <list>
#include <string.h>

#include <beaengine/BeaEngine.h>

#include "unittest/regression/table_reader.hpp"
#include "unittest/regression/dasm_sexp.hpp"
#include "unittest/regression/dasm_result.hpp"
#include "unittest/regression/Timer.h"

// ===================================================================
static void do_disasm_test (const char* table_file, dasm_result_c& result)
{
  std::cout << "Loading table from " << table_file << std::endl;
  table_reader_c reader (table_file);
  std::cout << "Table loaded. Number of entries: " 
	    << reader.items () << std::endl;
  char place [sizeof(DISASM)];

  for (size_t i=0; i<reader.items (); i++)
    {
      const table_item_c& ti = reader.at (i);

      memset (place, 0, sizeof(DISASM));
      DISASM* dasm = new (place) DISASM;
      
      dasm->EIP = (UIntPtr) ti.bytes ();
      Timer timer;
      timer.start ();
      int len = Disasm (dasm);
      timer.stop ();
      double e = timer.getElapsedTimeInMicroSec ();
      result.add (dasm, ti, len, e);
    }
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
      dasm_result_c dasm_results ("test", "bugbug");
      do_disasm_test (table_file, dasm_results);
      dasm_to_sexp (std::cout, dasm_results);
      return 0;
    }
  catch (std::exception& e)
    {
      std::cerr << "Error: " << e.what () << std::endl;
    }
  return 1;
}
