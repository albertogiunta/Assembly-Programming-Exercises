#include <stdio.h>

void main() {
	//variabili
	unsigned int num = 0x80000001;
	unsigned int ris; //risultato: 1 se è potenza di 2, altrimento 0

	//blocco assembler
	__asm {
		
				XOR EAX, EAX		;EAX = risultato

				CMP EAX, 0
				JE Fine

				CMP 










		Fine:
	}

	//stampa su video
	printf("Risultato = %d\n", ris);
	char c = getchar();
}