#include <sstream>
#include "unittest/regression/dasm_xml.hpp"

static std::string print_bytes (unsigned char* code, size_t length)
{
  std::ostringstream os;
  size_t i;
  for (i=0; i<length; i++)
    {
      os << "0x";
      os.width (2);
      os.fill  ('0');
      os.flags  (std::ios::hex);
      unsigned int x = (code [i] & 0xFF);
      os << x;
      if (i < length - 1)
	{
	  os << " ";
	}
    }
  return os.str ();
}
// ---------------------------------------------------------------------
template <typename T>
static std::string elem (const std::string& name, const T& v)
{
  std::ostringstream os;
  os << "</" << name << " val=\"0x" << std::hex << v << "\">" << std::dec
     << std::endl;
  return os.str ();
}
// ---------------------------------------------------------------------
static std::string elem (const std::string& name, const UInt64& v)
{
  std::ostringstream os;
  os << "</" << name << " val=\"0x" << std::hex << (unsigned long)v << "\">" << std::dec
     << std::endl;
  return os.str ();
}
// ---------------------------------------------------------------------
static std::string elem (const std::string& name, const Int64& v)
{
  std::ostringstream os;
  os << "</" << name << " val=\"0x" << std::hex << (long)v << "\">" << std::dec
     << std::endl;
  return os.str ();
}

static std::string elem (const std::string& name, const unsigned char& v)
{
  std::ostringstream os;
  os << "</" << name << " val=\"0x" << std::hex << ((unsigned int)v & 0xFF) << "\">" << std::dec
     << std::endl;
  return os.str ();
}
// ---------------------------------------------------------------------
static std::string elem (const std::string& name, const char* v)
{
  std::ostringstream os;
  os << "</" << name << " val=\"" << v << "\">" << std::dec
     << std::endl;
  return os.str ();
}
// ---------------------------------------------------------------------
static std::ostream& print_memory_info (std::ostream& os, const MEMORYTYPE* m)
{
  const std::string ident1 ("\t\t\t");
  const std::string ident2 = ident1 + '\t';
  os << ident1 << "<Memory>" << std::endl
     << ident2 << elem ( "BaseRegister" , m->BaseRegister)
     << ident2 << elem ( "IndexRegister", m->IndexRegister)
     << ident2 << elem ( "Scale"        , m->Scale)
     << ident2 << elem ( "Displacement" , m->Displacement)
     << ident1 << "</Memory>" << std::endl;
  return os;
}
// ---------------------------------------------------------------------
static std::ostream& print_arg_type (std::ostream& os, const ARGTYPE* a, const char* name)
{
  const std::string ident1 ("\t\t");
  const std::string ident2 = ident1 + '\t';
  os << ident1 << "<" << name << ">" << std::endl
     << ident2 << elem ( "ArgMnemonic", a->ArgMnemonic)
     << ident2 << elem ( "ArgType"    , a->ArgType)
     << ident2 << elem ( "ArgSize"    , a->ArgSize)
     << ident2 << elem ( "AccessMode" , a->AccessMode)
     << ident2 << elem ( "SegmentReg" , a->SegmentReg);
  print_memory_info (os, &a->Memory)
    << ident1 << "</" << name << ">" << std::endl;
  return os;
}
// ---------------------------------------------------------------------
static std::ostream& print_efl_struct (std::ostream& os, const EFLStruct* e)
{
  const std::string ident1 ("\t\t\t");
  const std::string ident2 = ident1 + '\t';
  
  os << ident1 << "<efl>" << std::endl
     << ident2 << elem ( "OF_", e->OF_)
     << ident2 << elem ( "SF_", e->SF_)
     << ident2 << elem ( "ZF_", e->ZF_)
     << ident2 << elem ( "AF_", e->AF_)
     << ident2 << elem ( "PF_", e->PF_)
     << ident2 << elem ( "CF_", e->CF_)
     << ident2 << elem ( "TF_", e->TF_)
     << ident2 << elem ( "IF_", e->IF_)
     << ident2 << elem ( "DF_", e->DF_)
     << ident2 << elem ( "NT_", e->NT_)
     << ident2 << elem ( "RF_", e->RF_)
     << ident2 << elem ( "alignment", e->alignment)
     << ident1 << "</efl>" << std::endl;
  return os;
}
// ---------------------------------------------------------------------
static std::ostream& print_instr_type (std::ostream& os, const INSTRTYPE* i)
{
  const std::string ident1 ("\t\t");
  const std::string ident2 = ident1 + "\t";
  os << ident1 << "<Instruction>" << std::endl
     << ident2 << elem ( "Category"            , i->Category)
     << ident2 << elem ( "Opcode"              , i->Opcode)
     << ident2 << elem ( "Mnemonic"            , i->Mnemonic)
     << ident2 << elem ( "BranchType"          , i->BranchType)
     << ident2 << elem ( "AddrValue"           , i->AddrValue)
     << ident2 << elem ( "Immediat"            , i->Immediat)
     << ident2 << elem ( "ImplicitModifiedRegs", i->ImplicitModifiedRegs);
  print_efl_struct (os, &i->Flags) 
    << ident1 << "</Instruction>" << std::endl;
  return os;
}
// ---------------------------------------------------------------------
static std::ostream& print_rex (std::ostream& os, const REX_Struct* e)
{
  const std::string ident1 ("\t\t\t");
  const std::string ident2 = ident1 + "\t";
  os << ident1 << "<REX>" << std::endl
     << ident2 << elem ( "W_", e->W_)
     << ident2 << elem ( "R_", e->R_)
     << ident2 << elem ( "X_", e->X_)
     << ident2 << elem ( "B_", e->B_)
     << ident2 << elem ( "state", e->state)
     << ident1 << "</REX>" << std::endl;
  return os;
}
// ---------------------------------------------------------------------
static std::ostream& print_prefix_info (std::ostream& os, const PREFIXINFO* e)
{
  const std::string ident1 ("\t\t");
  const std::string ident2 = ident1 + '\t';
  os << ident1 << "<Prefix>" << std::endl
     << ident2 << elem ( "Number"        , e->Number)
     << ident2 << elem ( "NbUndefined"   , e->NbUndefined)
     << ident2 << elem ( "LockPrefix"    , e->LockPrefix)
     << ident2 << elem ( "OperandSize"   , e->OperandSize)
     << ident2 << elem ( "AddressSize"   , e->AddressSize)
     << ident2 << elem ( "RepnePrefix"   , e->RepnePrefix)
     << ident2 << elem ( "RepPrefix"     , e->RepPrefix)
     << ident2 << elem ( "FSPrefix"      , e->FSPrefix)
     << ident2 << elem ( "SSPrefix"      , e->SSPrefix)
     << ident2 << elem ( "GSPrefix"      , e->GSPrefix)
     << ident2 << elem ( "ESPrefix"      , e->ESPrefix)
     << ident2 << elem ( "CSPrefix"      , e->CSPrefix)
     << ident2 << elem ( "DSPrefix"      , e->DSPrefix)
     << ident2 << elem ( "BranchTaken"   , e->BranchTaken)
     << ident2 << elem ( "BranchNotTaken", e->BranchNotTaken);
  print_rex (os, &e->REX)
     << ident1 << "</Prefix>" << std::endl;
  return os;
}
// ---------------------------------------------------------------------
void dasm_to_xml (std::ostream& os, const DISASM& dasm, int dasm_len, const table_item_c& expected)
{
  const std::string ident1 ("\t");
  const std::string ident2 = ident1 + '\t';
  os << ident1 << "<asm>" << std::endl
     << ident2 << elem ( "expected", expected.mnemonics ().c_str ())
     << ident2 << "</opcode val=\"" << print_bytes (expected.bytes (), expected.length ()) << "\"/>" 
     << std::endl;
     
  if (dasm_len == UNKNOWN_OPCODE)
    {
      os << ident2 << elem ( "status", "failed")
	 << ident1 << "</asm>" << std::endl;
      return;
    }
  if ((size_t) dasm_len != expected.length ())
    {
      os << ident2 << elem ( "status", "failed")
	 << ident2 << elem ( "mnemonics", (const char*) dasm.CompleteInstr)
	 << ident1 << "</asm>" << std::endl;
      return;
    }
  os << ident2 << elem ( "options", dasm.Options);
  print_instr_type  (os, &dasm.Instruction);
  print_arg_type    (os, &dasm.Argument1, "Argument1");
  print_arg_type    (os, &dasm.Argument2, "Argument2");
  print_arg_type    (os, &dasm.Argument3, "Argument3");
  print_prefix_info (os, &dasm.Prefix)
    << ident1 << "</asm>" << std::endl;
}
