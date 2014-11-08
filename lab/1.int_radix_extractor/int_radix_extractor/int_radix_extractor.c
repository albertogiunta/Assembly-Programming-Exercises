#include <stdio.h>

////////////////////// SOLUZIONE PROF /////////////////////////////////////


/*void main() {
	unsigned int num = 10;
	unsigned int radix;

	__asm {

			MOV radix, 0
			MOV EAX, 1

			; si potrebbe fare SUB radix, EAX ma in questo modo radix verrebbe modificata

			MOV EBX, num
	Ciclo : SUB EBX, EAX

				CMP EBX, 0;
			JL Fine; devo usare un salto con segno altrimenti non scatterebe mai dato che CMP considera EBX con segno
			INC radix
			ADD EAX, 2
			JMP Ciclo
	Fine :

	}

	printf("Radice -- = %d\n", radix);
} */


////////////////////// MIA SOLUZIONE /////////////////////////////////////

void main() {
	//Variabili
	unsigned int num = 1;
	unsigned int radice;

	//Blocco assembler
	__asm {
			MOV radice, 0
			MOV EAX, 1

			MOV EBX, num	;così non comprometto il valore di num

	Ciclo:	SUB EBX, EAX

			CMP EBX, 0
			JL Fine			;se è minore di 0, quindi se è vero, termina

			INC radice		;altrimenti incrementa radice, aggiungi 2 a eax e salta incondizionato a Ciclo:
			ADD EAX, 2
			JMP Ciclo
				
	Fine:
	}

	//Stampa a video
	printf("Radice = %d", radice);
	char c = getchar();
}