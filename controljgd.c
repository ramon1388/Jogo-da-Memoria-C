#include <windows.h>
#include <time.h>
#include "controljgd.h"

//Função criada para passar a vez para o proximo jogador.
void passarvez(){
	//Switch criado para verificar quantos jogadores a no jogo, assim informar de quem e a proxima vez.
	switch(control.jogadores){
		case 2:
			limparlc(13,30);
			if(control.vez==1){
				control.vez=2;
				printfxy(13,30,"Vez do(a) jogador(a) %s",j2.nome);
			} else {
				control.vez=1;
				printfxy(13,30,"Vez do(a) jogador(a) %s",j1.nome);
			}
			break;
		case 3:
			limparlc(13,30);
			if(control.vez==1){
				control.vez=3;
				printfxy(13,30,"Vez do computador");
				jogadacomp();
			} else {
				control.vez=1;
				printfxy(13,30,"Vez do(a) jogador(a) %s",j1.nome);
			}
			break;
	} 
}

//Atualizar informações no menu informações.
void attinfo(){
	//Tela 1 jogador.
	if(control.jogadores==1){
		printfxy(16,25,"Acertos:");
		
		printfxy(19,23,"%s:",j1.nome);
		printfxy(19,33,"%d",j1.acertos);
		
		printfxy(16,53,"Erros:");
		printfxy(19,50,"%s:",j1.nome);
		printfxy(19,59,"%d",j1.erros);
		
	//Tela 2 jogadores.
	} else if(control.jogadores == 2 || control.jogadores == 3){
		//titulo acertos
		printfxy(16,11,"Acertos:");
		//tiulo erros
		printfxy(16,57,"Erros:");
		
		//nomep1
		printfxy(19,12,"%s:",j1.nome);
		//acertosp1
		printfxy(19,22,"%d",j1.acertos);
		
		//nomep1
		printfxy(19,58,"%s:",j1.nome);
		//errosp1
		printfxy(19,67,"%d",j1.erros);
		
		if(control.jogadores==2){
			//nomep2
			printfxy(21,12,"%s:",j2.nome);
			//acertosp2
			printfxy(21,22,"%d",j2.acertos);
			
			//nomep2
			printfxy(21,58,"%s:",j2.nome);
			//errosp2
			printfxy(21,67,"%d",j2.erros);
			
		} else if(control.jogadores==3){
			//nomePC
			printfxy(21,12,"COMP:");
			//acertosPC
			printfxy(21,22,"%d",comp.acertos);
			
			//nomePC
			printfxy(21,58,"COMP:");
			//errosPC
			printfxy(21,67,"%d",comp.erros);
		}
	}
}

//Verificar a jogada do jogador 1/2 ou computador.
int verifjogada(int jogd1,int jogd2,int Ljogada1,int Ljogada2,int Cjogada1,int Cjogada2,int var1,int var2){
	//Condição criada para verificar se o player acertou ou errou a jogada.
	if(jogd1==jogd2){
		
		for(int i=0;i<linha;i++){
			for(int j=0;j<coluna;j++){
				if(control.matriz[i][j]==jogd1) control.matriz[i][j]=0;
			}
		}
		
		switch(control.vez){
			case 1:
				j1.acertos++;
				break;
			case 2:
				j2.acertos++;
				break;
			case 3:
				comp.acertos++;
				attinfo();
				if(j1.acertos + j2.acertos + comp.acertos != 8) jogadacomp();
				break;
			}
	} else {
		switch(control.vez){
			case 1:
				j1.erros++;
				break;
			case 2:
				j2.erros++;
				break;
			case 3:
				comp.erros++;
				break;
		}
		attinfo();
		Sleep(1000);
		//Se o player errou, o "#" ira ser printado nas mesmas posições que ele escolheu para que o numero seja coberto novamente.
		if(control.vez==1||control.vez==2){
			printfxy(var1,var2,"#");
			printfxy(control.l2,control.c1+1,"#");
		} else if(control.vez==3){
			printfxy(Ljogada1,Cjogada1,"#");
			printfxy(Ljogada2,Cjogada2,"#");
		}
		//Passa a vez para o proximo jogador.
		if(control.jogadores!=1){
			passarvez();
		}
	}
}

//Função para que o computador faça sua jogada.
void jogadacomp(){
	int Ljogada1=0,Ljogada2=0,Cjogada1=0,Cjogada2=0,val1=0,val2=0;
	srand(time(NULL));
	//Pega uma posição valida na matriz.
	do{
		Ljogada1=rand()%4;
		Ljogada2=rand()%4;
		Cjogada1=rand()%4;
		Cjogada2=rand()%4;
	}while((Ljogada1==Ljogada2 && Cjogada1==Cjogada2) || (control.matriz[Ljogada1][Cjogada1]==0 || control.matriz[Ljogada2][Cjogada2]==0));
	
	//Armazena os numeros escolhido pelo computador na matriz.
	val1 = control.matriz[Ljogada1][Cjogada1];
	val2 = control.matriz[Ljogada2][Cjogada2];
	
	//Move o cursor na tela dependendo de qual posição na tabela o computador escolheu, servira para printar os numeros na posição correta.
	Ljogada1+=5,Ljogada2+=5;
	if(Cjogada1==0) Cjogada1=37;
	else if(Cjogada1==1) Cjogada1=39;
	else if(Cjogada1==2) Cjogada1=41;
	else if(Cjogada1==3) Cjogada1=43;
	if(Cjogada2==0) Cjogada2=37;
	else if(Cjogada2==1) Cjogada2=39;
	else if(Cjogada2==2) Cjogada2=41;
	else if(Cjogada2==3) Cjogada2=43;
	
	//Printa os que foram escolhidos na matriz pelo computador.
	Sleep(1000);
	printfxy(Ljogada1,Cjogada1,"%d",val1);
	Sleep(1000);
	printfxy(Ljogada2,Cjogada2,"%d",val2);

	//Verifica a jogada do computador.
	verifjogada(val1,val2,Ljogada1,Ljogada2,Cjogada1,Cjogada2,0,0);
}
