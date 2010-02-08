#include <stdexcept>
#include <memory>

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "unittest/regression/table_reader.hpp"

static std::runtime_error raise (const char* text, int line)
{
  const size_t BUFF_LEN = 1024;
  char buff [BUFF_LEN];
  const char* format = "%s [line %d]";
#if !defined(BEA_LACKS_SNPRINTF)
  snprintf (buff, BUFF_LEN, format, text, line);
#else
  _snprintf (buff, BUFF_LEN, format, text, line);
#endif
  return std::runtime_error (std::string (buff));
}

static std::runtime_error raise (const char* text, const char* text2)
{
  const size_t BUFF_LEN = 1024;
  char buff [BUFF_LEN];
  const char* format = "%s %s";
#if !defined(BEA_LACKS_SNPRINTF)
  snprintf (buff, BUFF_LEN, format, text, text2);
#else
  _snprintf (buff, BUFF_LEN, format, text, text2);
#endif
  return std::runtime_error (std::string (buff));
}

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
unsigned int table_item_c::line_number () const
{
  return m_line_num;
}
// ----------------------------------------------------------------------
table_item_c::table_item_c (const char* table_line, unsigned int line_num)
  : m_line_num (line_num)
{
  if (!table_line)
    {
      throw raise ("Can not parse empty line", line_num);
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
  size_t i;
  for (i=0; i<len; i++)
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
      throw raise ("mnemonics missing", line_num);
    }
  // opcode always consists of even number of hexdigits
  m_length = end_of_opcode - start_of_opcode;
  if (m_length % 2 == 1)
    {
      throw raise ("opcode always consists of even number of hexdigits",
		   line_num);
    }
  m_mnemonics = std::string (table_line + start_of_mnem, len - start_of_mnem);
  m_length = m_length / 2;
  m_opcode = new unsigned char [m_length];

  std::auto_ptr <unsigned char> opcode_guard (m_opcode);

  for (i = 0; i<m_length; i++)
    {
      const char a = table_line [start_of_opcode + (2*i)];
      const char b = table_line [start_of_opcode + (2*i) + 1];
      if (!isxdigit (a) || !isxdigit (b))
	{
	  throw raise ("not a hex digit in opcode", line_num);
	}

      char abval [] = {a, b, 0};
      unsigned int val = 0;
      sscanf (abval, "%x", &val);
      
      m_opcode [i] = (unsigned char)(val & 0xFF);
    }
  opcode_guard.release ();
}

// =============================================================
// table_reader_c
// =============================================================
struct auto_closer_s
{
  auto_closer_s (FILE* f)
    : m_file (f)
  {
  }
  ~auto_closer_s ()
  {
    fclose (m_file);
  }
  FILE* m_file;
};

table_reader_c::table_reader_c (const char* table_file)
{
  FILE* f = fopen (table_file, "rb");
  if (f == NULL)
    {
      throw raise ("Can not open file for read:", table_file);
    }
  auto_closer_s auto_closer (f);
  std::string line;
  unsigned int line_num = 1;
  int state = 0;

  while (!feof (f))
    {
      char ch;
      fread (&ch, 1, 1, f);
      if (ch == '\n' || ch == '\r')
	{
	  if (state == 1)
	    {
	      m_table.push_back (table_item_c (line.c_str (), line_num));
	      state = 0;
	      line = "";
	      line_num++;
	    }
	}
      else
	{
	  state = 1;
	  line = line + ch;
	}
    }
}
// -------------------------------------------------------------
size_t table_reader_c::items ()
{
  return m_table.size ();
}
// -------------------------------------------------------------
const table_item_c& table_reader_c::at (size_t i)
{
  return m_table.at (i);
}

