#include <stdio.h>

void main() {
	unsigned int num = 4;
	unsigned int ris; // = 1 se è potenza di 2, altrimenti 0

	//blocco assembly
	/*__asm {

				XOR EAX, EAX	;EAX = risultato
				MOV EBX, num	;EBX = numero

				CMP EBX, 0		;compara EBX e 0
				JE	Fine		;se sono uguali va alla fine

				CMP EBX, 1		; compara EBX e 0
				JE Fine			; se sono uguali va alla fine

	FaiTest:	TEST EBX, 00000001b		;fai AND tra EBX e 00000001
				JNZ Comp1				;se il registro è uguale da zero vai allo shift
		
				SHR EBX, 1				;fai lo shift destro su EBX di un bit
				JMP FaiTest				;torna al TEST

	Comp1:		CMP EBX, 1				;compara il numero con 1
				JNE Fine				;se sono uguali vai a fine
				
				MOV EAX, 1				;altrimenti fa diventare il risultato 1


	Fine:		MOV ris, EAX			;metti il risultato in ris
	}*/

	__asm {
		XOR EAX, EAX
			MOV ECX, num; EBX = numero

			JECXZ Fine

			NEG ECX; nega bit a bit, fa 0 - REGISTRO

			AND ECX, num; faccio l end bit a bit con num

			CMP ECX, num; se non sono uguali vado alla fine
			JNE Fine

			INC EAX; se sono uguali vuol dire che è potenza di 2

		Fine:		MOV ris, EAX
	}
	//stampa risultato
	printf("Risultato = %d\n", ris);
	if (ris == 1) {
		printf("Potenza del due");
	} else {
		printf("non potenza del due");
	}
	char c = getchar();

}