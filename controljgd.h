#ifndef CONTROLJGD_H
#define CONTROLJGD_H

#define linha 4
#define coluna 4
#define MAX_NOME 5

struct jogadores{
	char nome[MAX_NOME];
	int acertos;
	int erros;
	float med;
	struct jogadores *prox;
}j1,j2,comp,rank;
typedef struct jogadores jogadoress;

struct controledejogada{
	int **matriz;
	int jogadores;
	int l2;
	int c1;
	int vez;
}control;

void passarvez();
void attinfo();
int verifjogada(int,int,int,int,int,int,int,int);
void jogadacomp();

void limparlc(int,int);
void printfxy(int,int,const char *, ...);

#endif
