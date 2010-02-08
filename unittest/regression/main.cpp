#include <iostream>
#include <iomanip>
#include <stdexcept>

#include <string.h>

#include <beaengine/BeaEngine.h>

#include "unittest/regression/table_reader.hpp"
#include "unittest/regression/dasm_xml.hpp"

int do_disasm_test (const char* table_file)
{
  std::cout << "Loading table from " << table_file << std::endl;
  table_reader_c reader (table_file);
  std::cout << "Table loaded. Number of entries: " 
	    << reader.items () << std::endl;

  for (size_t i=0; i<reader.items (); i++)
    {
      const table_item_c& ti = reader.at (i);
      DISASM dasm;
      memset (&dasm, 0, sizeof(DISASM));
      dasm.EIP = (UIntPtr) ti.bytes ();
      int len = Disasm (&dasm);
      dasm_to_xml (std::cout, dasm, len, ti);
    }
  return 0;
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
      return do_disasm_test (table_file);
    }
  catch (std::exception& e)
    {
      std::cerr << "Error: " << e.what () << std::endl;
    }
  return 1;
}
