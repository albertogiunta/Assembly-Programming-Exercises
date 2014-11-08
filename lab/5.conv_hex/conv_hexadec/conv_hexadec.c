#include <stdio.h>

void main() {
	//variabili
	unsigned int num = 439041615;
	unsigned char ris[8];

	//blocco assembler
	__asm {

				MOV ECX, 7			;ECX = i
				XOR EAX, EAX		;EAX = val
				MOV EDI, num
	inizio:		MOV EBX, EDI		;EBX = temp
				AND EBX, 15
				
				CMP EBX, 9
				JG se_magg

				MOV EAX, 48
				JMP risult

	se_magg:	MOV EAX, 55

	risult:		MOV EDX, EAX
				ADD EDX, EBX
				MOV ris[ECX], DL
				SHR EDI, 4
				DEC ECX

				CMP ECX, 0
				JGE inizio

				JMP fine
	fine:
}

	unsigned int i;
	for (i = 0; i < 8; i++) {
		printf("%c", ris[i]);
	}
	printf("\n");
	char c = getchar();
}