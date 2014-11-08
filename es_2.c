/********************************************************************************
*                                                                              *
*                   Architetture dei sistemi di Elaborazione                   *
*                                                                              *
********************************************************************************

Elaborato 1
Descrizione:	Dato un intero a 32 bit (inteso con segno), costruirne la rappresentazione
floating point (IEEE 754 a singola precisione), restituendo la rappresentazione
binaria (come stringa C di 32 caratteri più carattere nullo finale) ed esadecimale
(come stringa C di 8 caratteri più il carattere nullo finale).
Si supponga che il numero sia sempre rappresentabile senza errori di arrotondamento.

********************************************************************************/


#include <stdio.h>
#include <stdlib.h>


void main() {
	// Variabili
	int Num = 2498;				// il numero (32 bit in complemento a 2)
	char RisultatoBin[33];		// da riempire con la rap. binaria del num. floating point
	char RisultatoHex[9];		// da riempire con la rap. esadecimale del num. floating point


	// Blocco assembler
	__asm {
				xor eax, eax
				mov eax, Num		;eax = num
				xor ebx, ebx		;ebx = contatore vettore
				xor ecx, ecx
				xor edx, edx
				xor esi, esi		;esi = bit del segno
				xor edi, edi

	;AZZERO I VETTORI
				mov ecx, 32					;metto il contatore a 32
				mov RisultatoBin[32], 0
				mov RisultatoHex[8], 0
		azz_vett_bin:						
				mov RisultatoBin[ecx-1], 48	;riempio il vettore binario di zeri
				loop azz_vett_bin

				mov ecx, 8					;metto il contatore a 8
		azz_vett_hex:
				mov RisultatoHex[ecx-1], 48	;riempio il vettore esadecimale di zeri
				loop azz_vett_hex		
				

	;METTO IL SEGNO NEL BINARIO
				cmp eax, 0					;comparo eax con 0		
				jg salta					;se eax > 0 vado a costruire la mantissa
				je fine						;se eax = 0 vado a fine (i vettori sono già pronti)
				mov esi, 0x80000000			;salvo il bit del segno negativo in esi
				neg eax						;nego eax così diventa positivo
				mov RisultatoBin[0], 49		;metto il bit del segno nella prima cella del vettore
		salta:
				mov ecx, 32					;metto il contatore a 32
				
		costr_mant:	
				shl eax, 1					;faccio uno shift left <-- di un bit alla volta su eax
				test eax, 0x80000000		;maschero il primo bit + significativo
				loopz costr_mant			;continuo finchè non è uno
				
				
				shl eax, 1					;scorro eax di 1 <-- sarebbe l 1, della mantissa
				dec ecx						;decremento di uno la dimensione della mantissa
				
		

		;TROVA E SCRIVI L ESPONENTE
				; ecx ha già dentro la dimensione dell esp
				mov ebx, ecx				;metto ecx in ebx, sarebbe il numero di cifre della mantissa, ovvero l esponente
				add ecx, 127				;aggiungo 127 all esponente
 				mov edx, ecx				;metto il valore dell esponente in edx
				mov edi, edx				;metto il valore dell esponente in edi, mi servirà nella riconversioned
				mov ecx, 8					;uso ecx per il ciclo per metterlo nel vettore, lo metto a 8
				
		inserisci_esp:
				test edx, 0x1				;se la cifra meno significativa dell esponente è 1 
				je scorri					;se non è uno salta a scorri, dato che è già inizializzato a 0
				mov RisultatoBin[ecx], 49	;altrimenti scrivi 1 in ascii
		scorri:
				shr edx, 1					;scorro edx --> di 1
				loop inserisci_esp			
					

		;SCRIVI LA MANTISSA NEL VETTORE
				mov ecx, 23					;metto in ecx 23
				shr eax, 9					;scorro la mantissa --> di 9 così è pronta per essere copiata, tolgo bit eccedenti la mantissa
				mov edx, eax				;metto in edx la mantissa prima di farci lavori sopra

		scrivi_mant:
				test eax, 0x1				;se il bit meno significativo della mantissa è 1
				jz scorri_mant				;se non è 1 scorro, dato che è inizializzato a 0
				mov RisultatoBin[ecx+8], 49	;se è 1 lo scrivo in ascii nel vettore
		scorri_mant :
				shr eax, 1					;scorro eax --> di 1
				loop scrivi_mant			



				mov ecx, 7					;metto ecx a 
				mov eax, edx				;rimetto la mantissa in eax così, per gusto
				xor ebx, ebx				;ebx = esponente
		conv_array:
				cmp RisultatoBin[ecx+1], 49	;se la cella in questione è 1
				jne fai_loop				;se non sono uguali scorro
				or ebx, 1					;altrimenti metto il bit in questione di ebx a 1
		fai_loop:
				shl ebx, 1
				loop conv_array


				shl edi, 23
				add eax, edi
				add eax, esi
				mov edi, eax		;in edi c è il bianario dell ieeeeeeeeeee 754

				MOV ECX, 7			;ECX = i
				XOR EAX, EAX		;EAX = val

	inizio:		MOV EBX, EDI		;EBX = temp
				AND EBX, 15
				
				CMP EBX, 9
				JG se_magg

				MOV EAX, 48
				JMP risult

	se_magg:	MOV EAX, 55

	risult:		MOV EDX, EAX
				ADD EDX, EBX
				MOV RisultatoHex[ECX], DL
				SHR EDI, 4
				DEC ECX

				CMP ECX, 0
				JGE inizio

				JMP fine

		fine:
	}

	// Stampa su video (i due numeri stampati come stringhe devono essere identici)
	
		char CheckRisultatoBin[33];
		float fNum = (float)Num;
		itoa(*(int*)&fNum, CheckRisultatoBin, 2);
		printf("La rappresentazione binaria del numero %d (floating point) e': \n%s\n%032s\n", Num, RisultatoBin, CheckRisultatoBin);
		printf("\nLa rappresentazione esadecimale del numero %d (floating point) e': \n%s\n%08X\n", Num, RisultatoHex, *(int*)&fNum);
	
		system("pause");
}

