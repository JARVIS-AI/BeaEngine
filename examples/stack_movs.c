#include <stdio.h>
#include <string.h>
#include "beaengine/BeaEngine.h"
/* ============================= Init datas */
DISASM MyDisasm;
int len;
int Error = 0;
void *pBuffer;
int  (*pSourceCode) (void); 	/* function pointer */

/* ================================================================================= */
/*																									*/
/*						Disassemble code in the specified buffer using the correct VA					*/
/*																									*/
/*==================================================================================*/

void DisassembleCode(char *StartCodeSection, char *EndCodeSection, int (*Virtual_Address)(void))
{

	Error = 0;

	/* ============================= Init EIP */
	MyDisasm.EIP = (int) StartCodeSection;
	/* ============================= Init VirtualAddr */
	MyDisasm.VirtualAddr = (Int64) Virtual_Address;

	/* ============================= set IA-32 architecture */
	MyDisasm.Archi = 0;
	/* ============================= Loop for Disasm */
	while ( !Error){
		/* ============================= Fix SecurityBlock */
		MyDisasm.SecurityBlock = (long) EndCodeSection - MyDisasm.EIP;

		len = Disasm(&MyDisasm);
		if (len == OUT_OF_BLOCK) {
			(void) printf("disasm engine is not allowed to read more memory \n");
			Error = 1;
		}
		else if (len == UNKNOWN_OPCODE) {
			(void) printf("unknown opcode");
			Error = 1;
		}
		else {
			/* ============================= Make a filter on Argument1 and Argument2 */
			if ((MyDisasm.Instruction.ImplicitModifiedRegs & REG4) || ((MyDisasm.Argument1.ArgType & REG4) && (MyDisasm.Argument1.AccessMode == WRITE)) || ((MyDisasm.Argument2.ArgType & REG4) && (MyDisasm.Argument2.AccessMode == WRITE))) {
				(void) puts(MyDisasm.CompleteInstr);
			}
			MyDisasm.EIP = MyDisasm.EIP + len;
			MyDisasm.VirtualAddr = MyDisasm.VirtualAddr + len;
			if (MyDisasm.EIP >= (int) EndCodeSection) {
				(void) printf("End of buffer reached ! \n");
				Error = 1;
			}
		}
	};
	return;
}

/* ================================================================================= */
/*																									*/
/*												MAIN												*/
/*																									*/
/*==================================================================================*/
int main(int argc, char* argv[])
{

	/* ============================= Init the Disasm structure (important !)*/
	(void) memset (&MyDisasm, 0, sizeof(DISASM));

	pSourceCode =  &main;
	pBuffer = malloc(100);
	/* ============================= Let's NOP the buffer */
	(void) memset (pBuffer, 0x90, 100);
	/* ============================= Copy 100 bytes in it */
	(void) memcpy (pBuffer,(void*)(int) pSourceCode, 100);

	(void) printf("******************************************************* \n");
	(void) printf("Display only instructions modifying ESP explicitly or implicitly. \n");
	(void) printf("******************************************************* \n");

	/* ============================= Select Display Option */
	MyDisasm.Options = Tabulation + MasmSyntax;
	/* ============================= Disassemble code located in that buffer */
	DisassembleCode (pBuffer, (char*) pBuffer + 100, pSourceCode);

	return 0;
}
