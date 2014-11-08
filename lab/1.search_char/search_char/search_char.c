#include <stdio.h>

void main() {
	//variabili
	char string[] = "Questa è una stringz";
	int lunghezza = sizeof(string)-1; //-1 PER NON INCLUDERE IL CARATTERE TERMINATORE /0
	char character = 's';
	int position = 0;

	//blocco assembler
	__asm {
				XOR EAX, EAX			;azzero eax che farà da contatore (I)

	Ciclo:		CMP EAX, lunghezza
				JGE NotFound			;se eax è greater or eaqual a lunghezza va a DecCont

				XOR EBX, EBX			;altrimenti azzera ebx, che conterrà la posizione del carattere
				MOV BL, string[EAX]		;avendo a che fare con un char utilizzo la parte a 8 byte di ebx
				CMP BL, character

				JE Fine					;se nel registro c è lo stesso valore del carattere va a fine

				INC EAX					;altrimenti incrementa il contatore e torna a Ciclo
				JMP Ciclo

	NotFound:	MOV EAX, -1
	Fine:		PUSH EAX				;metto il valore di eax nello stack e lo tiro fuori mettendolo in position
				POP position
				
	
				;NB se eax (cioè il contatotre) è = 19 vuol dire che è arrivato in fondo ai cicli e non ha trovato niente

	}

	//stampa su video 
	if (position == -1) {
		printf("Carattere non trovato !!!");
	}
	else {
		printf("Posizione = %d", position);
	}
	char c = getchar();
}