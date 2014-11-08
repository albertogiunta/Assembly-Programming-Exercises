#include <stdio.h>
#include <stdlib.h>

void main() {
	//VARIABILI
	unsigned int Num = 1254154; //variabile double word
	char ris[8];

	//BLOCCO ASSEMBLER
	__asm {

	}

	//STAMPA SU VIDEO
	{
		unsigned int i;
		for (int i = 0; i < 8; i++) {
			printf("%c", Ris[i]);
		}
		printf("\n");
	}
}