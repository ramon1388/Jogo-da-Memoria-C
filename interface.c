#include "stdio.h"
#include "interface.h"
#include "controljgd.h"
#include "conio.h"

//Fun��o feita para criar a interface das informa��es dos jogadores.
void criarmenujogo(){
	if(control.jogadores==1){
		//Apenas 1 player.
		printf("\n\t************************* - Informa��es - ***********************\n");
		printf("\t**                                                             **\n");
		printf("\t**                                                             **\n");
		printf("\t**                                                             **\n");
		printf("\t**            *************              *************         **\n");
		printf("\t**            |           |              |           |         **\n");
		printf("\t**            *************              *************         **\n");
		printf("\t**                                                             **\n");
		printf("\t**                                                             **\n");
		printf("\t**                                                             **\n");
		printf("\t*****************************************************************");
	}else if(control.jogadores==2 || control.jogadores==3){
		//Contra computador ou 2p
		printf("\n\t************************* - Informa��es - ***********************\n");
		printf("\t**                                                             **\n");
		printf("\t**                                                             **\n");
		printf("\t**                                                             **\n");
		printf("\t** *************                                 ************* **\n");
		printf("\t** |           |                                 |           | **\n");
		printf("\t** *************                                 ************* **\n");
		printf("\t** |           |                                 |           | **\n");
		printf("\t** *************                                 ************* **\n");
		printf("\t**                                                             **\n");
		printf("\t*****************************************************************");
	}
}

//Fun�ao feita para voltar a tela do menu.
int voltarmenu(){
	printf("\n\nPressione a tecla (v) para voltar.");
	char var;
	do{
		var=getch();
	}while(var!='v' && var!='V');
	return 1;
}

//Zerar informa��es do jogador.
void limparinfos(){
	j1.erros=0;
	j1.acertos=0;
	j1.med=0;
	j2.acertos=0;
	j2.erros=0;
	j2.med=0;
	comp.acertos=0;
	comp.erros=0;
	comp.med=0;
}
