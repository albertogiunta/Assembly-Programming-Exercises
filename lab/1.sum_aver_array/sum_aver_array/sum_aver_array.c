#include <stdio.h>

void main() {
	//variabili
	//int vettore[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, -1, -2, -3 };
	int vettore[] = { -1, -2 };
	unsigned int lunghezza = sizeof(vettore) / sizeof(int);
	int somma;
	int media;

	/////////////////////////  SOLUZIONE MIA //////////////////////////////////////////////////////////////////

	//blocco assembler
	/*__asm {
				XOR EAX, EAX		;EAX = somma				
				XOR EBX, EBX		;EBX = lunghezza
				MOV EBX, lunghezza
				


	Ciclo:		ADD EAX, vettore[EBX*4-4]	;faccio *4 perchè sto trattando numeri che occupano 4byte. -4 perchè lo scorro al contrario,
											;quindi arrivo in fondo e torno indietro di un elemento (ovvero 4 byte)
				DEC EBX						;decremento il contatore lunghezza

				CMP EBX, 0					;controllo se sono arrivato al primo elemento (dato che parto da in fondo)
				JNE Ciclo					;se non è = 0 ripeto il ciclo altrimenti continuo

				MOV somma, EAX				;salvo il valore di EAX nella variabile SOMMA
											;EAX continua a contenere la somma, sarà il dividendo

				CDQ							;converte (estendendo il segno) la DWORD EAX nella QWORD EDX:EAX
											;NB va eseguita subito prima della divisione

				IDIV lunghezza				;NB divide il registro EAX per il registro EBX (è con segno)

				MOV media, EAX				;dopo la divisione in EAX c è il quoziente (intero), in EDX il resto
											;sposto il quoziente nella variabile media
	}*/


	/////////////////////////  SOLUZIONE PROF //////////////////////////////////////////////////////////////////
	__asm {
				MOV somma, 0
				MOV ECX, lunghezza
		Ciclo:	MOV EBX, vettore[ECX*4-4]
				ADD somma, EBX
				LOOP Ciclo

				MOV EAX, somma
				CDQ
				IDIV lunghezza

				MOV media, EAX
	}

	//stampa a video
	printf("Somma = %d\n", somma);
	printf("Media = %d\n", media);
	char c = getchar();
}