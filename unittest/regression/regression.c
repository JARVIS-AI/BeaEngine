#include <beaengine/BeaEngine.h>

#include <stdio.h>
#include <string.h>

void print_bytes (unsigned char* code, size_t length)
{
	size_t i;
	for (i=0; i<length; i++)
	{
		(void)printf ("0x%02X", (code [i] & 0xFF));
		if (i < length - 1)
		{
			(void)printf (" ");
		}
	}
}

void print_memory_info (MEMORYTYPE* m)
{
	(void)printf ("\t\t\t<Memory>\n");
	(void)printf ("\t\t\t\t</BaseRegister val=\"0x%X\">\n", m->BaseRegister);
	(void)printf ("\t\t\t\t</IndexRegister val=\"0x%X\">\n", m->IndexRegister);
	(void)printf ("\t\t\t\t</Scale val=\"0x%X\">\n", m->Scale);
	(void)printf ("\t\t\t\t</Displacement val=\"0x%X\">\n", m->Displacement);
	(void)printf ("\t\t\t</Memory>\n");
}

void print_arg_type (ARGTYPE* a, char* name)
{
	(void)printf ("\t\t<%s>\n", name);
	(void)printf ("\t\t\t</ArgMenmonic val=\"%s\">\n", a->ArgMnemonic);
	(void)printf ("\t\t\t</ArgType val=\"0x%X\">\n", a->ArgType);
	(void)printf ("\t\t\t</Argsize val=\"0x%X\">\n", a->ArgSize);
	(void)printf ("\t\t\t</AccessMode val=\"0x%X\">\n", a->AccessMode);
	(void)printf ("\t\t\t</SegmentReg val=\"0x%X\">\n", a->SegmentReg);
	print_memory_info (&a->Memory);
	(void)printf ("\t\t</%s>\n", name);
}

void print_efl_struct (EFLStruct* e)
{
	(void)printf ("\t\t\t<efl>\n");
	(void)printf ("\t\t\t\t</OF_ val=\"0x%X\">\n", e->OF_);
	(void)printf ("\t\t\t\t</SF_ val=\"0x%X\">\n", e->SF_);
	(void)printf ("\t\t\t\t</ZF_ val=\"0x%X\">\n", e->ZF_);
	(void)printf ("\t\t\t\t</AF_ val=\"0x%X\">\n", e->AF_);
	(void)printf ("\t\t\t\t</PF_ val=\"0x%X\">\n", e->PF_);
	(void)printf ("\t\t\t\t</CF_ val=\"0x%X\">\n", e->CF_);
	(void)printf ("\t\t\t\t</TF_ val=\"0x%X\">\n", e->TF_);
	(void)printf ("\t\t\t\t</IF_ val=\"0x%X\">\n", e->IF_);
	(void)printf ("\t\t\t\t</DF_ val=\"0x%X\">\n", e->DF_);
	(void)printf ("\t\t\t\t</NT_ val=\"0x%X\">\n", e->NT_);
	(void)printf ("\t\t\t\t</RF_ val=\"0x%X\">\n", e->RF_);
	(void)printf ("\t\t\t\t</alignment val=\"0x%X\">\n", e->alignment);
	(void)printf ("\t\t\t</efl>\n");
}

void print_instr_type (INSTRTYPE* i)
{
	(void)printf ("\t\t<Instruction>\n");
	(void)printf ("\t\t\t</Category val=\"0x%X\">\n", i->Category);
	(void)printf ("\t\t\t</Opcode val=\"0x%X\">\n", i->Opcode);
	(void)printf ("\t\t\t</Mnemonic val=\"%s\">\n", i->Mnemonic);
	(void)printf ("\t\t\t</BranchType val=\"0x%X\">\n", i->BranchType);
	(void)printf ("\t\t\t</AddrValue val=\"0x%X\">\n", i->AddrValue);
	(void)printf ("\t\t\t</Immediat val=\"0x%X\">\n", i->Immediat);
	(void)printf ("\t\t\t</ImplicitModifiedRegs val=\"0x%X\">\n", i->ImplicitModifiedRegs);
	print_efl_struct (&i->Flags);
	(void)printf ("\t\t</Instruction>\n");
}

void print_rex (REX_Struct* e)
{
	(void)printf ("\t\t\t<REX>\n");
	(void)printf ("\t\t\t\t</W_ val=\"0x%X\">\n", e->W_);
	(void)printf ("\t\t\t\t</R_ val=\"0x%X\">\n", e->R_);
	(void)printf ("\t\t\t\t</X_ val=\"0x%X\">\n", e->X_);
	(void)printf ("\t\t\t\t</B_ val=\"0x%X\">\n", e->B_);
	(void)printf ("\t\t\t\t</state val=\"0x%X\">\n", e->state);
	(void)printf ("\t\t\t</REX>\n");
}

void print_prefix_info (PREFIXINFO* e)
{
	(void)printf ("\t\t<Prefix>\n");
	(void)printf ("\t\t\t</Number val=\"0x%X\">\n", e->Number);
	(void)printf ("\t\t\t</NbUndefined val=\"0x%X\">\n", e->NbUndefined);
	(void)printf ("\t\t\t</LockPrefix val=\"0x%X\">\n", e->LockPrefix);
	(void)printf ("\t\t\t</OperandSize val=\"0x%X\">\n", e->OperandSize);
	(void)printf ("\t\t\t</AddressSize val=\"0x%X\">\n", e->AddressSize);
	(void)printf ("\t\t\t</RepnePrefix val=\"0x%X\">\n", e->RepnePrefix);
	(void)printf ("\t\t\t</RepPrefix val=\"0x%X\">\n", e->RepPrefix);
	(void)printf ("\t\t\t</FSPrefix val=\"0x%X\">\n", e->FSPrefix);
	(void)printf ("\t\t\t</SSPrefix val=\"0x%X\">\n", e->SSPrefix);
	(void)printf ("\t\t\t</GSPrefix val=\"0x%X\">\n", e->GSPrefix);
	(void)printf ("\t\t\t</ESPrefix val=\"0x%X\">\n", e->ESPrefix);
	(void)printf ("\t\t\t</CSPrefix val=\"0x%X\">\n", e->CSPrefix);
	(void)printf ("\t\t\t</DSPrefix val=\"0x%X\">\n", e->DSPrefix);
	(void)printf ("\t\t\t</BranchTaken val=\"0x%X\">\n", e->BranchTaken);
	(void)printf ("\t\t\t</BranchNotTaken val=\"0x%X\">\n", e->BranchNotTaken);
	print_rex (&e->REX);
	(void)printf ("\t\t</Prefix>\n");
}

int do_disasm (unsigned char* code, size_t length, const char* exp)
{
	DISASM MyDisasm;
	(void)printf ("\t<asm>\n");
	(void)printf ("\t\t<expected val=\"%s\">\n", exp);
	memset (&MyDisasm, 0, sizeof(DISASM));
	MyDisasm.EIP = (long)code;	
	int len = Disasm (&MyDisasm);
	(void)printf ("\t\t</opcode val=\"");
	print_bytes	(code, length);
	(void)printf ("\">\n");
	if (len == UNKNOWN_OPCODE) 
	{
		(void)printf ("\t\t</status value=\"failed\">\n");
		(void)printf ("\t</opcode>\n");
		return 0;
	}
	if (len != length)
	{
		(void)printf ("\t\t</status value=\"failed\">\n");
		(void)printf ("\t\t</mnemonics val=\"%s\">\n", (char*) MyDisasm.CompleteInstr);
		(void)printf ("\t</opcode>\n");
		return 0;
	}
	(void)printf ("\t\t</options val=\"%X\">\n", MyDisasm.Options);
	print_instr_type (&MyDisasm.Instruction);
	print_arg_type (&MyDisasm.Argument1, "Argument1");
	print_arg_type (&MyDisasm.Argument2, "Argument2");
	print_arg_type (&MyDisasm.Argument3, "Argument3");
	print_prefix_info (&MyDisasm.Prefix);
	(void)printf ("\t</asm>\n");
	return 1;	
}

void xml_begin ()
{
	(void)printf ("<disasm>\n");
}

void xml_end ()
{
	(void)printf ("</disasm>\n");
}
#include "opcodes.inc"

#define DASM(X, Z) (void)do_disasm (X, sizeof (X), Z)
int main ()
{
	xml_begin ();
	
	#include "code.inc"
	
	xml_end ();
	return 0;
}
