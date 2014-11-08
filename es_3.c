/********************************************************************************
*                                                                              *
*                   Architetture dei sistemi di Elaborazione                   *
*                                                                              *
********************************************************************************

Elaborato 3
Descrizione:	Data una DWORD, trovare le sequenze contigue più lunghe
di bit a 0 e a 1 e restituirne le rispettive lunghezze.

********************************************************************************/


#include <stdio.h>


void main() {

	// Variabili
	unsigned int w = 0x00300001;	// la DWORD

	int numSequenzaZero;	// Lunghezza della sequenza più lunga di bit a 0 contigui
	int numSequenzaUno;     // Lunghezza della sequenza più lunga di bit a 1 contigui

	__asm {

		mov eax, w			; numero
		xor ebx, ebx		; contatore d'appoggio per ogni serie di zeri
		xor edx, edx		; contatore d'appoggio per ogni serie di uni
		mov ecx, 32			; contatore generale(conta i bit del numero)
		xor esi, esi		; contatore zeri
		xor edi, edi		; contatore uni
	
	fai_test :
		test eax, 1			; guardo se il bit è zero o uno
		jne se_uno			; se è uno salto a se_uno
							; altrimenti se zero
		xor edx, edx		; azzero il contatore di uni parziale
		inc ebx				; incremento il contatore parziale di zeri
		cmp esi, ebx
		cmovl esi, ebx
		jmp fai_shift		; vado a fai_shift

	se_uno :
		xor ebx, ebx		; azzero il contatore di zeri parziale
		inc edx				; se il bit è uno incremento il contatore parziale di uni
							; (e vado in automatico a fai_shift)
		cmp edi, edx	
		cmovl edi, edx

	fai_shift:
		shr eax, 1			; shift right sul numero di un 1 bit
		loop fai_test		; decremento ecx di uno e controllo se zero.se > 0 vai a fari_test, sennò esci

	fine :
		mov numSequenzaZero, esi
		mov numSequenzaUno, edi

	}

	// Stampa su video
	printf("La sequenza più lunga di bit contigui a 0 è pari a %d\n", numSequenzaZero);
	printf("La sequenza più lunga di bit contigui a 1 è pari a %d\n", numSequenzaUno);
	system("pause");
}
