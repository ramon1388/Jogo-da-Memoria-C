//Bibliotecas:
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <stdarg.h>
#include <locale.h>
#include "controljgd.h"
#include "rank.h"
#include "mcursor.h"
#include "interface.h"

FILE *arq;

int main(){
	//Definições iniciais.
	system("title Jogo da memoria");
	setlocale(LC_ALL, "Portuguese");
	//Goto feito para voltar ao menu.
	menu:
	system("cls");
	system("color 1f");
	
	//Cria o menu principal.
	printf("\t*****************************************************************\n");
	printf("\t**************************** - MENU - ***************************\n");
	printf("\t*****************************************************************\n");
	printf("\t***                                                           ***\n");
	printf("\t***                    1 - Jogar                              ***\n");
	printf("\t***                    2 - Creditos                           ***\n");
	printf("\t***                    3 - Ranking                            ***\n");
	printf("\t***                    4 - Sair                               ***\n");
	printf("\t***                                                           ***\n");
	printf("\t*****************************************************************\n");
	printf("\t*****************************************************************\n");
	printf("\t*****************************************************************\n");

	//Switch que pega a tecla pressionada pelo player com o "getch" e verifica se e algumas das opções.
	switch(getch()){
		//Iniciar o jogo.
		case '1':
			//Alocação da matriz
			control.matriz = (int **) malloc(sizeof(int *)*linha);
			for(int i=0;i<=linha;i++){
				control.matriz[i] = (int *) malloc(sizeof(int)*coluna);
				
			}
			
			//Menu para escolha da quantidade de jogadores.
			do{
				jogadores:
				system("cls");
				printf("\n\t*****************************************************************\n");
			    printf("\t********************** - JOGO DA MEMORIA - **********************\n");
			    printf("\t*****************************************************************\n");
			    printf("\t**                                                             **\n");
				printf("\t**                       1. Um jogador                         **\n");
				printf("\t**                       2. Dois jogadores                     **\n");
				printf("\t**                       3. Jogar contra o computador          **\n");
				printf("\t**                       v. Voltar                             **\n");
				printf("\t**                                                             **\n");
				printf("\t*****************************************************************\n");
				printf("\t*****************************************************************\n");
				printf("\t*****************************************************************\n");
				
				//Switch que pega a tecla que o player pressionou e verificar se e algumas dessas.
				switch(getch()){
					case '1':
						control.jogadores = 1;
						break;
					case '2':
						control.jogadores = 2;
						break;
					case '3':
						control.jogadores = 3;
						break;
					case 'v':
					case 'V':
						goto menu;
						break;
					default:
						printf("Opção invalida.\n");
						Sleep(1000);
						system("cls");
						break;	
				}
				
			}while(control.jogadores == 0);
			
			//Pega o(s) nome(s) do(s) jogador(es).
			if(control.jogadores!=0){
				system("cls");
				switch(control.jogadores){
					case 1:
					case 3:
						voltar1:
						printf("Informe seu nome(minimo: 1 caractere, maximo: 6 characteres): \n");
						scanf("%s",&j1.nome);
						if(strlen(j1.nome)>MAX_NOME){
							printf("Nome invalido.");
							Sleep(1000);
							system("cls");
							goto voltar1;
							break;
						}
						break;
		
					case 2:
						do{
							printf("Informe o nome do jogador 1(1-6 characteres): \n");
							scanf("%s",&j1.nome);
							printf("Informe o nome do jogador 2(1-6 characteres): \n");
							scanf("%s",&j2.nome);
							system("cls");
						}while(strlen(j1.nome)>MAX_NOME || strlen(j2.nome)>MAX_NOME || !strcmp(j1.nome,j2.nome));
						break;
				}
			}
			//Loop feito para zerar todas as posiçoes da matriz.
				for(int i=0;i<linha;i++){
					for(int j=0;j<coluna;j++){
						control.matriz[i][j]=0;
					}
				}
			
				srand(time(NULL));
				
				int num=8,l11=0,c11=0,c22=0,l22=0;
		
			//Loop feito para preencher a matriz com os pares de 1 a 8.
				while(num){
					l11=rand()%4;
					c11=rand()%4;
					c22=rand()%4;
					l22=rand()%4;
					
					if(control.matriz[c11][l11]==0 && control.matriz[c22][l22]==0 && (c11 != c22 || l11 != l22)){
						control.matriz[c11][l11] = num;
						control.matriz[c22][l22] = num;
						num--;
					}
				}
		
				system("cls");
				
			    int var1=0,var2=0,fim=0,Ppos=0,Spos=0,erros=0,pos1=0,l1=0,c2=0,pos2=0,key=0,PosPorVez=0,jogd1=0,jogd2=0;
			    
				//Defini a primeira jogada para o jogador 1.
			    control.vez=1;
			    //Criação da interface do jogo.
			    printfxy(0,8,"v. Voltar");
			    printf("\n\t*****************************************************************\n");
			    printf("\t********************** - JOGO DA MEMORIA - **********************\n");
			    printf("\t*****************************************************************\n");
			    printf("\t**                                                             **\n");
				printf("\t**                           # # # #                           **\n");
				printf("\t**                           # # # #                           **\n");
				printf("\t**                           # # # #                           **\n");
				printf("\t**                           # # # #                           **\n");
				printf("\t**                                                             **\n");
				printf("\t*****************************************************************\n");
				printf("\t*****************************************************************\n");
				printf("\t*****************************************************************\n");
				criarmenujogo(); //Cria o menu das informações.
				attinfo(); //Função criada para atualizar as informações dos jogadores.
		
				l1=5; //Define em qual linha o cursor inicializara.
				control.c1=36; //Define em qual coluna o cursor inicializara.
				
				printfxy(13,30,"Vez do(a) jogador(a) %s",j1.nome); //Print para informa de quem e a vez.
			//Loop feito para que o jogador possa controlar sua jogada atraves das setas do teclado.
			do{	
			    gotoxy(l1,control.c1);
			    printf(">");
				
			    if(kbhit){
					key=getch();
				}
				
				if(key == 118 || key == 86){
					limparinfos();
					goto jogadores;
				}
				
				//seta para baixo
				if(key == 80 && pos1 < 3){
					control.l2=l1;
					l1++;
					pos1++;
				}
				
				//seta para cima		
			    else if(key == 72 && pos1 >= 1){
					control.l2=l1;
					l1--;
					pos1--;
				}
				
				//seta para direita	
				else if(key==77 && pos2 < 3){
					c2=control.c1;
					control.c1+=2;
					pos2++;
				}
				
				//seta para esquerda	
				else if(key==75 && pos2 >= 1){
					c2=control.c1;
					control.c1-=2;
					pos2--;
				}
		
				//Apagar seta anterior
			    if(l1!=control.l2){
					printfxy(control.l2,control.c1," ");
					control.l2=l1;
				}
						
			    if(control.c1!=c2 && key==77){
					printfxy(control.l2,control.c1-2," ");
					c2=control.c1;
				}
						
				if(control.c1!=c2 && key==75){
					printfxy(control.l2,control.c1+2," ");
					c2=control.c1;
				}
				
				//Verifica qual se ainda e o primeiro ou segundo numero q o player escolheu.
				if(PosPorVez < 2 && key==13 && control.matriz[pos1][pos2]){
					gotoxy(l1,control.c1+1);
					printf("%d",control.matriz[pos1][pos2]);
					PosPorVez++;
					if(PosPorVez==1){
						jogd1=control.matriz[pos1][pos2];
						var1=control.l2;
						var2=control.c1+1;
					}
				}
						
				if(PosPorVez==2 && key== 13){
					if(PosPorVez==2 && (var1==control.l2 && var2==control.c1+1)){
						PosPorVez--;
					} else {
						jogd2=control.matriz[pos1][pos2];	
						verifjogada(jogd1,jogd2,0,0,0,0,var1,var2);
						PosPorVez=0;
						attinfo();
					}
			 	}
			 	fim= j1.acertos + j2.acertos + comp.acertos;
			}while(fim<8);
			
			//Printa o reultado ao fim do jogo.
			if(control.jogadores==1){
				
				printfxy(23,25,"Jogo finalizado.");
				
			} else if(control.jogadores==2){
				
				if(j1.acertos > j2.acertos)printfxy(23,25,"Vitoria do jogador %s.",j1.nome);
				else if(j2.acertos > j1.acertos) printfxy(23,25,"Vitoria do jogador %s.",j2.nome);
				else printfxy(23,25,"O jogo empatou.");
			
			} else if(control.jogadores==3){
				
				if(j1.acertos > comp.acertos) printfxy(23,25,"Vitoria do jogador %s.",j1.nome);
				else if(comp.acertos > j1.acertos) printfxy(23,25,"Vitoria do jogador Computador.",comp.acertos);
				else printfxy(23,25,"O jogo empatou.");
			}
			
			//Armazena as informaões no arquivo.
			if(fim==8 && control.jogadores != 3){
				arq=fopen("rank.txt","ab");
				if(arq==NULL){
					printf("Nâo foi possivel abrir o arquivo.");
					exit(0);
				}
		
				j1.med=(float)j1.acertos/(float)j1.erros;
				fwrite(&j1,sizeof(jogadoress),1,arq);
				
				if(control.jogadores==2){
					j2.med=(float)j2.acertos/(float)j2.erros;
					fwrite(&j2,sizeof(jogadoress),1,arq);
				}
				fclose(arq);
				limparinfos();
				if(voltarmenu()) goto menu;
			}
			break;
		//Creditos.
		case '2':
			system("cls");
			printf("ESTE jOGO FOI DESENVOLVIDO POR:\n\nRamon Araujo\nLuiz Carlos\nCicero Jose");
			if(voltarmenu()) goto menu;
			break;
			
		//Abrir arquivo para pegar as informações dos jogadores e coloca-las na lista.
		case '3':
			{
			system("cls");
			jogadoress *lista=NULL;

			arq=fopen("rank.txt","rb");

			if(arq==NULL){
				printf("Não foi possivel abrir o arquivo.");
				if(voltarmenu()) goto menu;
			}else{
				while(fread(&rank,sizeof(jogadoress),1,arq)){
					lista=preencherrank(lista,rank.nome,rank.acertos,rank.erros,rank.med);
				}
				//Zerar todas as variaveis dos jogadores.
				//Mostrar o ranking.
				mostrarrank(lista);
				//Pergunta se o player deseja volta para o menu.
				if(voltarmenu()) goto menu;
				//Libera o espaço na memoria que a lista precisou utilizar.
				limparlista(lista);
				//Fechar o arquivo.
				fclose(arq);
				break;
				}
			}
		//Sair.
		case '4':
			exit(0);
			break;
		//Caso nao seja nenhuma das opçõe.
		default:
			printf("\nOpçao invalida!!!\n");
			system("color 4");
			Sleep(500);
			goto menu;
	}
}
