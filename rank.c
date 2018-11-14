#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "controljgd.h"
#include "rank.h"

//Função criada para limpar toda a memoria utilizada pela lista.
void limparlista(jogadoress *lista){
	while(lista){
		free(lista);
		lista->prox;
	}
}

//Função criada para preencher a lista com as informações dos jogadores que estao no arquivo.
jogadoress *preencherrank(jogadoress *lista,char nome[MAX_NOME],int acertos,int erros,float media){
	jogadoress *novo=criarrank(),*at,*ant;
	
	strcpy(novo->nome,nome);
	novo->acertos=acertos;
	novo->erros=erros;
	novo->med=media;


    at = lista;
    ant = NULL;

	if(lista == NULL){
		lista=novo;
		novo->prox=NULL;

    }else{
    	//Organiza a lista, para quem tem a melhor media.
		while(at != NULL && at->med > media){
    	    ant = at;
		    at = at->prox;
  	  	}

        novo->prox = at;
        if(ant == NULL){
            lista = novo;
        } else{
            ant->prox = novo;
        }
	}

	return lista;
}

//Função criada para mostrar o ranking para o jogador.
void mostrarrank(jogadoress *lista){
	jogadoress *lista2=lista;
	int top5=0;
	int l=1;
	int posrank=1;
	printf("|POS|  NOME  |  A  |  E  |  MED  |\n");
	printf("|---|--------|-----|-----|-------|");
	while(lista2!=NULL && top5++ < 5){
		gotoxy(0,0);
		printfxy(l+l,0,"| %d | %s ",posrank++,lista2->nome);
		printfxy(l+l,13,"|  %d  |",lista2->acertos);
		printfxy(l+l,20,"  %d  |",lista2->erros);
		printfxy(l+l,26,"  %.2f |\n",lista2->med);
		printf("|---|--------|-----|-----|-------|\n");
		l++;
		lista2=lista2->prox;
	}
}

//Aloca um espaço na memoria para a proxima posição da lista.
jogadoress *criarrank(){
	jogadoress *lista = (jogadoress *) malloc(sizeof(jogadoress));
	if(lista==NULL){
		printf("Erro na alocação da lista do ranking.");
		exit(0);
	}
	return lista;
}
