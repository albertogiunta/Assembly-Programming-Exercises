#include <stdio.h>

void main() {
	//variabili
	unsigned int num = 5;
	int ris;

	//istruzione assembler
	__asm {
				MOV EAX, num	;EAX = num
				XOR EBX, EBX	;EBX = 2
				XOR EDI, EDI	;d
				XOR EDX, EDX	;resto
				MOV EBX, 2

				CMP EAX, 2		;se num = 2 so già che è primo
				JE primo

				CMP EAX, 2		;se num < 2 so già che non è primo (per convenzione)
				JL non_primo

				DIV EBX			;num/2	
								;EAX = num/2 --- EBX = 2 --- ECX = resto
						
				MOV EBX, 2		;metto in EDI il numero per cui divido (2, 3, 4...)
				MOV EDI, EAX	;ECX = maxdiv ----- metto il risultato di num/2 in ECX
				
			oper_mod :
				MOV EAX, num	;reinizializzo EAX = num
				DIV EBX			;EAX / EDI

				CMP ECX, 0
				JE non_primo

				INC EBX
				CMP EBX, EDI
				JL oper_mod
				JMP primo

			primo:		
				MOV ris, 1
				JMP fine
			non_primo:	
				MOV ris, 0
				JMP fine
			fine:
	}

	//stampa su video
	printf("Risultato = %d\n", ris);
	system("PAUSE");
}