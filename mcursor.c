#include <stdio.h>
#include <windows.h>
#include "mcursor.h"

//Função criada para ir a uma determinada posição e printar espaçoes nela. ou seja (limpar linha e coluna) da posição escolhida.
void limparlc(int l,int c){
	for(int i=0;i<40;i++){
		gotoxy(l,c+i);
		printf(" ");
		gotoxy(l,c);
	}
}

//Função criada para manipular o cursor na tela do player.
void gotoxy(int a,int b){
    COORD c;
    c.Y = a;
    c.X = b;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

//Função criada para ir a uma determinada posição e printar alguma coisa nela.
void printfxy(int l,int c,const char *format, ...){
    char msg[100];
    va_list var;
    va_start(var,format);
    vsprintf(msg, format, var);
    va_end(var);

	gotoxy(l,c);
	for (int i = 0; i < strlen(msg); i++) {
		putc(msg[i],stdout);
	}
}
