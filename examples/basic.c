#include <stdio.h>
#include <string.h>

#include <beaengine/BeaEngine.h>

int main(int argc, char* argv [])
{
	/* ============================= Init datas */
	DISASM MyDisasm;
	int false = 0, true = 1;
	int len, i = 0;
	int Error = 0;

	/* ============================= Init the Disasm structure (important !)*/
	(void) memset (&MyDisasm, 0, sizeof(DISASM));

	/* ============================= Init EIP */
	MyDisasm.EIP = (UIntPtr) &main;

	/* ============================= Loop for Disasm */
	while ((!Error) && (i<20)){
		len = Disasm(&MyDisasm);
		if (len != UNKNOWN_OPCODE) {
			(void) puts(MyDisasm.CompleteInstr);
			MyDisasm.EIP = MyDisasm.EIP + len;
            i++;
		}
		else {
			Error = 1;
		}
	};
	return 0;
}
