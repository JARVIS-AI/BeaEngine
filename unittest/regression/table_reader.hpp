#ifndef __REGRESSION_TABLE_READER_HPP__
#define __REGRESSION_TABLE_READER_HPP__

#include <string>
#include <vector>

/**
 * These classes represents table.dasm file.
 * table.dasm file consists of text lines, where
 * each line consists of opcode and mnemonic.
 */
class table_reader_c;
/**
 * This class represents one line of table.dasm
 */
class table_item_c 
{
  friend class table_reader_c;
public:
  table_item_c () {}

  /**
   * copy constructor
   */
  table_item_c (const table_item_c& item);

  /**
   * assigment operator
   */
  table_item_c& operator = (const table_item_c& item);

  /**
   * destructor
   */
  ~table_item_c ();

  /**
   * returns opcode bytes
   */
  unsigned char* bytes  () const;

  /**
   * returns length of the opcode bytes
   */
  size_t length () const;

  /**
   * returns the mnemonics of the opcode
   */
  std::string mnemonics () const;
  /**
   * returns the number of line in table file of this instruction
   */
  unsigned int line_number () const;
private:
  /**
   * this constructor parses the raw input line.
   */
  table_item_c (const char* table_line, unsigned int line_num);
private:
  unsigned char* m_opcode;	/**< opcode bytes */
  size_t         m_length;	/**< length of the opcode bytes */
  std::string    m_mnemonics;	/**< mnemonics */
  unsigned int   m_line_num;
};

/**
 * This class reads the table.dasm file and constructs 
 * vector of the table_items
 */
class table_reader_c 
{
public:
  /** 
   * reads table.dasm file. In case of error, empty table will be constructed
   * 
   * @param table_file - path to the table.dasm
   */
  table_reader_c (const char* table_file);
  
  /**
   * returns number of items in the table dasm
   */
  size_t items ();

  /**
   * returns i-th @c table_item_c. If i is out of range, the exception will
   * be thrown
   */ 
  const table_item_c& at (size_t i);
private:
  typedef std::vector <table_item_c> items_table_t;
private:
  items_table_t m_table;	/**< vector of the @c table_item_c */
};


#endif
