#include <stdio.h>

void main() {
	//variabili
	int vett[] = {1,3,2,4,5};
	unsigned int lung = sizeof(vett) / sizeof(vett[0]);

	//assembler
	__asm {
				DEC lung
				MOV EAX, lung				;EAX = pos
				
	Inizio:		MOV EBX, vett[EAX*4]		;EBX = max
				MOV ECX, EAX				;ECX = maxpos
				MOV ESI, EAX				;ESI = L
	DecL:		DEC ESI						;decremento ESI

				CMP ESI, -1		
				JNE Contr1					;se L diverso -1 salta a Contr1

				MOV EDI, vett[EAX*4]		;EDI = temp
				MOV vett[EAX*4], EBX
				MOV vett[ECX*4], EDI
				DEC EAX

				CMP EAX, 0
				JNG Fine

				JMP Inizio

	Contr1:		CMP EBX, vett[ESI*4]
				JG DecL						;se max > vett[L] salta a DecL

				MOV EBX, vett[ESI*4]		;altrimenti max = vett[L]
				MOV ECX, ESI
				JMP DecL


	Fine:


	}


	//stampa del risultato
	unsigned int i;
	for (i = 0; i <= lung; i++) {
		printf("vettore[%2d] = %d\n", i, vett[i]);
	}
	char c = getchar();
}