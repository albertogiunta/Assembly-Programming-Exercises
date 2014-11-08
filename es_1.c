/********************************************************************************
*                                                                              *
*                   Architetture dei sistemi di Elaborazione                   *
*                                                                              *
********************************************************************************

Elaborato 1
Descrizione: Dato un array di puntatori a stringa (ogni cella del vettore contiene
l'indirizzo a 32 bit del primo carattere della stringa), ordinarlo
alfabeticamente. Ogni stringa termina con il carattere nullo
(codice ASCII 0).

********************************************************************************/

#include <stdio.h>

void main() {
	// Le stringhe da ordinare (array di puntatori)
	char *strings[] = { "aaac", "ae", "aaab", "aaad", "aaaa" };
	// Il numero di stringhe nell'array
	int num = sizeof(strings) / sizeof(strings[0]);

	__asm {
	     xor eax, eax            ;eax = [esi]
         xor ebx, ebx            ;ebx = contatore del confronto
         xor ecx, ecx            ;ecx = contatore del comparato con tutti gli altri
         xor edx, edx            ;edx = bonus
         xor esi, esi            ;esi = indirizzo del comparato con tutti gli altri
         xor edi, edi            ;edi = indirizzo del confronto
         
         dec ecx           ;metto ecx uguale al primo elemento

    se_inc_ecx:
         inc ecx
         cmp ecx, num
         je fine
         mov ebx, ecx             ;metto ebx uguale al secondo elemento
         
    cicla:
         inc ebx
         cmp ebx, num
         je se_inc_ecx   

         mov esi, strings[ecx*4] ;metto in esi l indirizzo del primo elemento
         mov edi, strings[ebx*4] ;metto in edi l indirizzo del secondo elemento
         mov ah, [esi]           ;metto in eax lindirizzo del puntatore al primo elemento
         cmp ah, [edi]           ;comparo il primo elemento col secondo

    cicla_a_caso:
         jg scambia              ;se primo > secondo vai a scambia
         jl cicla                ;se primo = secondo vai a incrementa contatore secondo
 
         xor edx, edx            ;azzero l offset
    se_uguali:          
         inc edx                 ;incremento l offset
         xor eax, eax            ;azzero eax
         mov ah, [esi+edx]       ;metto in ah le lettere della prima parola
         mov al, [edi+edx]       ;metto in al le lettere della seconda parola

         cmp al, 0               ;comparo la seconda lettera con 0
         jne seconda_ne_zero     ;se diversa da 0 vado a sec_ne_zero,altrimenti vado a controllare la prima
         cmp ah, 0               ;comparo la prima lettera con 0
         je cicla                ;se sono entrambe zero ciclo perchè fottesega
         jne scambia             ;se non è uguale a zero e la seconda si, le scambio

    seconda_ne_zero:          
         cmp ah, al              ;comparo le due lettere (che sono diverse da zero)
         je se_uguali            ;se sono uguali cicla sulle lettere
         jmp cicla_a_caso        ;altrimenti cicla in cima sulle lettere nel ciclo principale

	scambia:
         mov strings[ecx*4], edi
         mov strings[ebx*4], esi
         jmp cicla

    fine:
	}

	// Stampa su video
	
	int i;
	for (i = 0; i<num; i++)
		printf("%s\n", strings[i]);
	
	system("pause");
}
