#include <iostream>
#include <string>
#include <stdio.h>
#include <list>
#include "unittest/regression/dasm_sexp.hpp"

#if !defined(BEA_LACKS_SNPRINTF)
  #define my_snprintf snprintf 
#else
  #define my_snprintf 
#endif

#if defined(__WATCOMC__)
#define OS_STR(V) (V.c_str ())
#else
#define OS_STR(V) V
#endif

#if defined(_MSC_VER)
        #define I64_FMT "I64"
#elif defined(__APPLE__)
        #define I64_FMT "q"
#else
        #define I64_FMT "ll"
#endif




class item_c
{
public:
  virtual ~item_c ();
  bool is_list () const
  {
    return m_is_list;
  }
  virtual const std::string& name () const = 0;
protected:
  item_c (bool lst)
    : m_is_list (lst)
  {
  }
private:
  bool m_is_list;
};

item_c::~item_c ()
{
}
// ====================================================================
class name_value_c : public item_c
{
public:
  name_value_c (const char* name, Int8 v);
  name_value_c (const char* name, UInt8 v);
  name_value_c (const char* name, Int16 v);
  name_value_c (const char* name, UInt16 v);
  name_value_c (const char* name, Int32 v);
  name_value_c (const char* name, UInt32 v);
  name_value_c (const char* name, Int64 v);
  name_value_c (const char* name, UInt64 v);
  name_value_c (const char* name, double v);
  name_value_c (const char* name, const char* v);
  name_value_c (const char* name, const std::string& v);


  const std::string& name () const;
  const std::string& value () const;
private:
  std::string m_name;
  std::string m_value;
};

#define BEA_NV_INIT(FMT, V)			\
  static const size_t BUFF_LEN = 64;		\
  static char BUFF [BUFF_LEN];			\
  my_snprintf (BUFF, BUFF_LEN, FMT, V);		\
  m_value = BUFF

// -----------------------------------------------------------------------
name_value_c::name_value_c (const char* name_, Int8 v)
  : item_c (false),
    m_name (name_)
{
  BEA_NV_INIT ("0x%X", (int)v & 0xFF);
}
// ------------------------------------------------------------
name_value_c::name_value_c (const char* name_, UInt8 v)
  : item_c (false),
    m_name (name_)
{
  BEA_NV_INIT ("0x%X", (int)v & 0xFF);
}
// ------------------------------------------------------------
name_value_c::name_value_c (const char* name_, Int16 v)
  : item_c (false),
    m_name (name_)
{
  BEA_NV_INIT ("0x%X", v);
}
// ------------------------------------------------------------
name_value_c::name_value_c (const char* name_, UInt16 v)
  : item_c (false),
    m_name (name_)
{
  BEA_NV_INIT ("0x%X", v);
}
// ------------------------------------------------------------
name_value_c::name_value_c (const char* name_, Int32 v)
  : item_c (false),
    m_name (name_)
{
  BEA_NV_INIT ("0x%X", v);
}
// ------------------------------------------------------------
name_value_c::name_value_c (const char* name_, UInt32 v)
  : item_c (false),
    m_name (name_)
{
  BEA_NV_INIT ("0x%X", v);
}
// ------------------------------------------------------------
name_value_c::name_value_c (const char* name_, Int64 v)
  : item_c (false),
    m_name (name_)
{
#if defined(BEA_HAVE_INT64) && !defined(BEA_LONG_IS_64_BIT)
  BEA_NV_INIT ("0x%"I64_FMT"X", v);
#else
  BEA_NV_INIT ("0x%lX", v);
#endif
}
// ------------------------------------------------------------
name_value_c::name_value_c (const char* name_, UInt64 v)
  : item_c (false),
    m_name (name_)
{
  #if defined(BEA_HAVE_INT64) && !defined(BEA_LONG_IS_64_BIT)
  BEA_NV_INIT ("0x%"I64_FMT"X", v);
#else
  BEA_NV_INIT ("0x%lX", v);
#endif
}
// ------------------------------------------------------------
name_value_c::name_value_c (const char* name_, const char* v)
  : item_c  (false),
    m_name  (name_),
    m_value (v)
{
}
// ------------------------------------------------------------
name_value_c::name_value_c (const char* name_, const std::string& v)
  : item_c  (false),
    m_name  (name_),
    m_value (v)
{
}
// ------------------------------------------------------------
name_value_c::name_value_c (const char* name_, double v)
  : item_c (false),
    m_name (name_)
{
  BEA_NV_INIT ("%f", v);
}
// ------------------------------------------------------------
const std::string& name_value_c::name () const
{
  return m_name;
}
// -----------------------------------------------------------
const std::string& name_value_c::value () const
{
  return m_value;
}
// ============================================================
class item_list_c : public item_c
{
public:
  typedef std::list <const item_c*>   item_list_t;
  typedef item_list_t::const_iterator iterator_t;
public:
  item_list_c (const char* name);
  ~item_list_c ();

  item_list_c* append (const item_c* item);

  iterator_t begin () const;
  iterator_t end () const;
  const std::string& name () const;
  
private:
  std::string m_name;
  item_list_t m_list;
};
// ---------------------------------------------------------------------
item_list_c::item_list_c (const char* name_)
  : item_c (true),
    m_name (name_)
{
}
// ---------------------------------------------------------------------
item_list_c::~item_list_c ()
{
  for (item_list_t::iterator i = m_list.begin (); i!=m_list.end (); i++)
    {
      delete *i;
    }
}
// ---------------------------------------------------------------------
item_list_c* item_list_c::append (const item_c* item)
{
  m_list.push_back (item);
  return this;
}
// ---------------------------------------------------------------------
item_list_c::iterator_t item_list_c::begin () const
{
  return m_list.begin ();
}
// ---------------------------------------------------------------------
item_list_c::iterator_t item_list_c::end () const
{
  return m_list.end ();
}
// ---------------------------------------------------------------------
const std::string& item_list_c::name () const
{
  return m_name;
}
// =====================================================================
static std::string print_bytes (unsigned char* code, size_t length)
{
  char bytes [6];
  std::string result;
  size_t i;
  for (i=0; i<length; i++)
    {
      unsigned int x = (code [i] & 0xFF);
      my_snprintf (bytes, 6, "0x%02X", x);
      result = result + (const char*)bytes;
      if (i < length - 1)
	{
	  result = result + " ";
	}
    }
  return result;
}
// ---------------------------------------------------------------------
template <typename T>
static name_value_c* elem (const char* name, const T& v)
{
  return new name_value_c (name, v);
}
// ---------------------------------------------------------------------
static item_list_c* print_memory_info (const MEMORYTYPE* m)
{
  item_list_c* elt = new item_list_c ("Memory");

  elt->append (elem ("BaseRegister" , m->BaseRegister))
    ->append  (elem ("IndexRegister", m->IndexRegister))
    ->append  (elem ("Scale"        , m->Scale))
    ->append  (elem ("Displacement" , m->Displacement));
  return elt;
}
// ---------------------------------------------------------------------
static item_list_c* print_arg_type (const ARGTYPE* a, const char* name)
{
  item_list_c* elt = new item_list_c (name);
  elt->append ( elem ( "ArgMnemonic", a->ArgMnemonic))
    ->append  ( elem ( "ArgType"    , a->ArgType))
    ->append  ( elem ( "ArgSize"    , a->ArgSize))
    ->append  ( elem ( "AccessMode" , a->AccessMode))
    ->append  ( elem ( "SegmentReg" , a->SegmentReg))
    ->append  ( print_memory_info (&a->Memory));
  return elt;
}
// ---------------------------------------------------------------------
static item_list_c* print_efl_struct (const EFLStruct* e)
{
  item_list_c* elt = new item_list_c ("efl");
  elt->append ( elem ( "OF_", e->OF_))
    ->append ( elem ( "SF_", e->SF_))
    ->append ( elem ( "ZF_", e->ZF_))
    ->append ( elem ( "AF_", e->AF_))
    ->append ( elem ( "PF_", e->PF_))
    ->append ( elem ( "CF_", e->CF_))
    ->append ( elem ( "TF_", e->TF_))
    ->append ( elem ( "IF_", e->IF_))
    ->append ( elem ( "DF_", e->DF_))
    ->append ( elem ( "NT_", e->NT_))
    ->append ( elem ( "RF_", e->RF_))
    ->append ( elem ( "alignment", e->alignment));
  return elt;
}
// ---------------------------------------------------------------------
static item_list_c* print_instr_type (const INSTRTYPE* i)
{
  item_list_c* elt = new item_list_c ("Instruction");

  elt->append ( elem ( "Category"            , i->Category))
    ->append  ( elem ( "Opcode"              , i->Opcode))
    ->append  ( elem ( "Mnemonic"            , i->Mnemonic))
    ->append  ( elem ( "BranchType"          , i->BranchType))
    ->append  ( elem ( "AddrValue"           , i->AddrValue))
    ->append  ( elem ( "Immediat"            , i->Immediat))
    ->append  ( elem ( "ImplicitModifiedRegs", i->ImplicitModifiedRegs))
    ->append  ( print_efl_struct (&i->Flags)); 
  return elt;
}
// ---------------------------------------------------------------------
static item_list_c* print_rex (const REX_Struct* e)
{
  item_list_c* elt = new item_list_c ("REX");
  elt->append ( elem ( "W_", e->W_))
    ->append ( elem ( "R_", e->R_))
    ->append ( elem ( "X_", e->X_))
    ->append ( elem ( "B_", e->B_))
    ->append ( elem ( "state", e->state));

  return elt;
}
// ---------------------------------------------------------------------
static item_list_c* print_prefix_info (const PREFIXINFO* e)
{
  item_list_c* elt = new item_list_c ("Prefix");
  elt
    ->append ( elem ( "Number"        , e->Number))
    ->append ( elem ( "NbUndefined"   , e->NbUndefined))
    ->append ( elem ( "LockPrefix"    , e->LockPrefix))
    ->append ( elem ( "OperandSize"   , e->OperandSize))
    ->append ( elem ( "AddressSize"   , e->AddressSize))
    ->append ( elem ( "RepnePrefix"   , e->RepnePrefix))
    ->append ( elem ( "RepPrefix"     , e->RepPrefix))
    ->append ( elem ( "FSPrefix"      , e->FSPrefix))
    ->append ( elem ( "SSPrefix"      , e->SSPrefix))
    ->append ( elem ( "GSPrefix"      , e->GSPrefix))
    ->append ( elem ( "ESPrefix"      , e->ESPrefix))
    ->append ( elem ( "CSPrefix"      , e->CSPrefix))
    ->append ( elem ( "DSPrefix"      , e->DSPrefix))
    ->append ( elem ( "BranchTaken"   , e->BranchTaken))
    ->append ( elem ( "BranchNotTaken", e->BranchNotTaken))
    ->append (print_rex (&e->REX));
  return elt;
}
// ---------------------------------------------------------------------
static item_list_c* dump_dasm (const DISASM& dasm, int dasm_len, const table_item_c& expected)
{
  item_list_c* elt = new item_list_c ("asm");
  elt->append (elem ("expected", expected.mnemonics ()))
    ->append (elem ("opcode", print_bytes (expected.bytes (), expected.length ())));
     
  if (dasm_len == UNKNOWN_OPCODE)
    {
      elt->append ( elem ( "status", "failed"));
      return elt;
    }
  if ((size_t) dasm_len != expected.length ())
    {
      std::string v (dasm.CompleteInstr);
      elt ->append ( elem ( "status", "failed"))
	->append ( elem ( "mnemonics", v));
      return elt;
    }
  elt ->append ( elem ( "options", dasm.Options))
    ->append (print_instr_type  (&dasm.Instruction))
    ->append (print_arg_type    (&dasm.Argument1, "Argument1"))
    ->append (print_arg_type    (&dasm.Argument2, "Argument2"))
    ->append (print_arg_type    (&dasm.Argument3, "Argument3"))
    ->append (print_prefix_info (&dasm.Prefix));
  return elt;
}
// ---------------------------------------------------------------------
static void dasm_to_sexp_helper (std::ostream& os, const item_c* item, unsigned int level)
{
  std::string ident;
  for (unsigned int i = 0; i<level; i++)
    {
      ident = ident + '\t';
    }
  if (item->is_list ())
    {
      os << OS_STR (ident) << "('" << OS_STR (item->name ()) << std::endl;
      const item_list_c* lst = (const item_list_c*) item;
      for (item_list_c::iterator_t itr = lst->begin (); itr != lst->end (); itr++)
	{
	  const item_c* itm = *itr;
	  dasm_to_sexp_helper (os, itm, level + 1);
	}
      os << OS_STR (ident) << ")" << std::endl;
    }
  else
    {
      const name_value_c* v = (const name_value_c*) item;
      os << OS_STR (ident) << "('" << OS_STR (v->name ()) 
	 << " \"" << OS_STR (v->value ()) << "\")" << std::endl;
    }
}
// ---------------------------------------------------------------------
void dasm_to_sexp (std::ostream& os, const dasm_result_c& rl)
{
  item_list_c* elt = new item_list_c ("disasm");
  item_list_c* md  = new item_list_c ("metadata");
  md->append  (elem ("name"      , rl.name ()))
    ->append  (elem ("comment"   , rl.comment ()))
    ->append  (elem ("entries"   , rl.size ()))
    ->append  (elem ("total-time", rl.total_time ()))
    ->append  (elem ("avg-time"  , rl.avg_time ()));
  elt->append (md);
  for (dasm_result_c::iterator_t i = rl.begin (); i!=rl.end (); i++)
    {
      elt->append (dump_dasm (*i->m_dasm, i->m_dasm_len, i->m_input));
    }
  dasm_to_sexp_helper (os, elt, 0);
  delete elt;
}
