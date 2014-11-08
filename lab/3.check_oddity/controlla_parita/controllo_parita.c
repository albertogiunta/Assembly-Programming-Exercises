#include <stdio.h>

void main () {
	//variabili
	unsigned char vett[] = { 254, 255, 255, 255, 255 };
	unsigned int lung = sizeof(vett) / sizeof(vett[0]);
	int ris; // 0: parità pari, 1: parità dispari

	//blocco assembler
	__asm {
				XOR EAX, EAX			; EAX = somma, inizializzo

				MOV ECX, lung			;metto la lunghezza in ECX
	ass_val:	MOV BH, vett[ECX-1]		;BH = val, ECX = lung

	ricom:		CMP BH, 0
				JZ val_zero

				TEST BH, 1
				JNZ se_pari

	scorri_dx:	SHR BH, 1
				JMP ricom

	se_pari:	INC EAX
				JMP scorri_dx

	val_zero:	DEC ECX
				CMP ECX, 0
				JNZ ass_val

				AND EAX, 1
				MOV ris, EAX
	}

	/*__asm {
		XOR EDX, EDX
		MOV ECX, lung
	
	Ciclo:
		MOV AL, vett[ECX - 1]

	Ciclo2:
		CMP AL, 0
		JE prox_byte
		TEST AL, 1
		JZ prox_bit
		INC EDX

	prox_bit:
		SHR AL, 1
		JMP Ciclo2

	prox_byte:
		LOOP Ciclo

		AND EDX, 1
		MOV ris, EDX
	}*/

	printf("ris= %d", ris);
	char c = getchar();
}