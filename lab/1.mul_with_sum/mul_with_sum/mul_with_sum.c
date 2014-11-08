#include <stdio.h>

void main() {
	unsigned short num1 = 3;
	unsigned short num2 = 5;
	unsigned int prod1, prod2, prod;

	__asm {

			; mio metodo ----------------------------------------------------------------------------

			XOR EAX, EAX	; azzero tutto il registro eax
			MOV AX, num1	; carico la variabile a 16 bit solo nella parte bassa del registro(ax), 
							; sono sicuro che nella parte alta non cambia perchè l ho azzerata prima
			
			XOR ECX, ECX
			MOV CX, num2	; usando LOOP, sono COSTRETTO ad usare ECX come variabile CONTATORE
			
			XOR EBX, EBX	; conterrà la somma finale

	Ciclo:	ADD EBX, EAX	; ebx contiene la somma delle ripetizioni delle somme di eax
			LOOP Ciclo
			
			PUSH EBX
			POP prod1


			; metodo meno efficiente ----------------------------------------------------------------

			XOR EBX, EBX
			XOR ECX, ECX
			MOV CX, num2

	Ciclo2 : ADD EBX, EAX
			DEC ECX
			JNZ Ciclo2

			PUSH EBX
			POP prod2


			; soluzione prof --------------------------------------------------------------------------

			MOV prod, 0

			XOR ECX, ECX
			MOV CX, num1

			XOR EAX, EAX
			MOV AX, num2
			
			;JCXZ Fine
			; oppure 
			CMP CX, 0
			JE Fine

	Ciclo3:	ADD prod, EAX
			LOOP Ciclo3

	Fine:
		
	}

	// PER VEDERE RISULTATO PREMI: fn + ctrl + f5
	printf("Prodotto (metodo prof)= %u\n", prod);
	printf("Prodotto  (mio metodo)= %u\n", prod1);
	printf("Prodotto (metodo meno efficiente)= %u\n", prod2);

	char c = getchar();
}