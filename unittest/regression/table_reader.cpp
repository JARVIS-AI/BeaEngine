#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <memory>

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "unittest/regression/table_reader.hpp"

// ==================================================
// table_item_c
// ==================================================
table_item_c::table_item_c (const table_item_c& item)
  : m_opcode    (0),
    m_length    (item.m_length),
    m_mnemonics (item.m_mnemonics)
{
  if (m_length > 0 && item.m_opcode)
    {
      m_opcode = new unsigned char [m_length];
      memcpy (m_opcode, item.m_opcode, m_length);
    }
}
// ----------------------------------------------------------------------
table_item_c& table_item_c::operator = (const table_item_c& item)
{
  if (this != &item)
    {
      if (m_opcode)
	{
	  delete m_opcode;
	  m_opcode = 0;
	}
      m_length    = item.m_length;
      m_mnemonics = item.m_mnemonics;
      if (m_length && item.m_opcode)
	{
	  m_opcode = new unsigned char [m_length];
	  memcpy (m_opcode, item.m_opcode, m_length);
	}
    }
  return *this;
}
// ----------------------------------------------------------------------
table_item_c::~table_item_c ()
{
  if (m_opcode)
    {
      delete [] m_opcode;
    }
}
// ----------------------------------------------------------------------
unsigned char* table_item_c::bytes  () const
{
  return m_opcode;
}
// ----------------------------------------------------------------------
size_t table_item_c::length () const
{
  return m_length;
}
// ----------------------------------------------------------------------
std::string table_item_c::mnemonics () const
{
  return m_mnemonics;
}
// ----------------------------------------------------------------------
table_item_c::table_item_c (const char* table_line, size_t line_num)
{
  if (!table_line)
    {
      std::ostringstream os;
      os << "Can not parse empty line (" << line_num << ")";
      throw std::runtime_error (os.str ());
    }
  size_t len = strlen (table_line);
  
  /*                 *\' '        ' '        *
                     +-+          +-+       +-+
                     | |          | |       | |
                     ^ |          ^ |       ^ |
         +---+ *\' '+---+  ' '   +---+     +---+
    ~~~~>| 0 |----->| 2 |------->| 3 |---->| 4 |
         +---+      +---+        +---+     +---+
           |          ^               
           | ' '      | *\' '         
           |        +---+
           +------->| 1 |
                    +---+ 

   */
  size_t start_of_opcode = 0;
  size_t end_of_opcode   = 0;
  size_t start_of_mnem   = 0;
  int state = 0;
  for (size_t i=0; i<len; i++)
    {
      char ch = table_line [i];
      switch (state)
	{
	case 0:
	  if (isspace (ch))
	    {
	      state = 1;
	    }
	  else
	    {
	      state = 2;
	      start_of_opcode = i;
	    }
	  break;
	case 1:
	  if (!isspace (ch))
	    {
	      state = 2;
	      start_of_opcode = i;
	    }
	  break;
	case 2:
	  if (isspace (ch))
	    {
	      state = 3;
	      end_of_opcode = i;
	    }
	  break;
	case 3:
	  if (!isspace (ch))
	    {
	      state = 4;
	      start_of_mnem = i;
	    }
	  break;
	}
      if (state == 4)
	{
	  break;
	}
    }
  if (state != 4)
    {
      std::ostringstream os;
      os << "mnemonics missing  (" << line_num << ")";
      throw std::runtime_error (os.str ());
    }
  // opcode always consists of even number of hexdigits
  m_length = end_of_opcode - start_of_opcode + 1;
  if (m_length % 2 == 1)
    {
      std::ostringstream os;
      os << "opcode always consists of even number of hexdigits  (" << line_num << ")";
      throw std::runtime_error (os.str ());
    }
  m_mnemonics.assign (table_line + start_of_mnem, table_line + len);
  m_length = m_length / 2;
  m_opcode = new unsigned char [m_length];

  std::auto_ptr <unsigned char> opcode_guard (m_opcode);

  for (size_t i = 0; i<m_length; i++)
    {
      const char a = table_line [start_of_opcode + 2*i];
      const char b = table_line [start_of_opcode + 2*i + 1];
      if (!isxdigit (a))
	{
	  std::ostringstream os;
	  os << "not a hex digit in opcode ("
	     << line_num << ":" << start_of_opcode + 2*i << ")";
	  throw std::runtime_error (os.str ());
	}
      if (!isxdigit (b))
	{
	  std::ostringstream os;
	  os << "not a hex digit in opcode ("
	     << line_num << ":" << start_of_opcode + 2*i + 1 << ")";
	  throw std::runtime_error (os.str ());
	}
      char abval [] = {a, b, 0};
      
      std::stringstream ss;
      ss << std::setbase (16) << abval;
      unsigned int val;
      ss >> val;
      m_opcode [i] = (unsigned char)(val & 0xFF);
    }
  opcode_guard.release ();
}
