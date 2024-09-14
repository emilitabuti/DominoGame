//DOM-ACER-View.cpp - Projeto Dominó
//13/09/2023
//Grupo: ACER
//André Garrido Macedo, Caroline Guimarães Campos, Emili Vieira Tabuti, Rafael de Mello Turaça

#include"DOM-ACER-View.h"
#include<stdio.h>
#include<iostream>
#include <windows.h>
using namespace std;


void fmostrartabuleiro(char status)
{
	int i, j , x;
	printf("\n");
	for(x = 0; x < 28 ; x++)
	{	
		if(peca[x].status == status)
			printf("[%d|%d] " , peca[x].lado1 , peca[x].lado2);
	}
	printf("\n");
}

int fmenu()
{
	int opc;
	printf("\nDomino Acer\n");
	printf(" _________\n");
	printf("|O  O|O   |\n");
	printf("| O  | O  |\n");
	printf("|O__O|___O|\n\n");
	printf("1- Iniciar jogo\n");
	printf("2- Regras\n");
	printf("3- Retomar jogo interrompido\n");
	printf("4- Salvar jogo\n");
	printf("5- Retomar jogo salvo\n");
	printf("0- Sair\n>");
	scanf("%d", &opc);
	
	return opc;
}

void fmaojogador()
{
	int i = 0;
	int n;
		printf("\n");
		printf("\njogador %c: ", jvez);
	
	for(n = 0 ; n <= 28; n++)
		if(peca[n].status == jvez)
		{
			printf("%c. [%d|%d] " ,alfabeto[i],  peca[n].lado1 , peca[n].lado2);
			i++;
		}
}

void apresentamesa()
{
	int P, i;
	printf("\n\n\n ");
	
	HANDLE console_color;
    console_color = GetStdHandle(
        STD_OUTPUT_HANDLE);
        
	for (i = 0; i < qtmesa; i++){
		P = 240;
        SetConsoleTextAttribute(
            console_color, P);
		printf("[%d|%d]",mesa[i].ladoE, mesa[i].ladoD);
		
		P = 15;
        SetConsoleTextAttribute(
            console_color, P);
        printf(" ");
    }
}

int apresentamenu2()
{
	int op;
	apresentamesa();
	fmaojogador();
	printf("\n1- Jogar peca(possiveis: %d ou %d): \n", mesaE , mesaD);
	printf("2- Comprar peca: \n");
	printf("3- Passar a vez: \n");
	printf("0- Interromper jogo\n>: ");
	scanf("%d", &op);
	return op;
}

char fjogapeca()
{
	char op;
	printf("Escolha a peca a ser jogada: ");
	scanf("%c", &op);
	return op;
}

char escolherLado()
{
	char c;
	do
	{
		printf("Escolha o lado da Mesa: Esquerdo/Direito (E/D): ");
		flush_in();
		scanf("%c",&c);
		c = toupper(c);
		if(c != 'E' && c != 'D' && c != 'e' && c != 'd')
			printf("letra invalida \n");
		
	}while(c != 'E' && c != 'D' && c != 'e' && c != 'd');
	
	return c;
}


int qntdjogadores()
{
	int modo;
	do
	{
	printf("\nQuantos jogadores?: ");
	printf("\n1 - 1 jogador");
	printf("\n2 - 2 jogadores \n");
	scanf("%d", &modo);
	if((modo != 1 )&&(modo != 2))
		{
			apresentamensagem("Quantidade de jogadores invalida");
		}
	}while((modo != 1 )&&(modo != 2));
	return modo;
}

void fregras() 
{
	system("cls");
	printf("Regras:\n");
	printf("  O jogo de domino contem 28 pecas com dois lados, e cada lado possui um numero de pontos, que varia de 0 a 6.\n\n");
	printf("  O jogador com a peca dupla-seis (peca com 6 pontos em ambos os lados) comeca o jogo. Se nenhum jogador tiver \ntal peca, o jogador com a maior peca dupla comeca ([5|5], [4|4], ..., [0|0]). Se nenhum jogador tambem nao \ntiver nenhuma peca dupla, o jogador com a peca de maior valor comeca ([6|5], [6|4], ...)\n\n");
	printf("  So e possivel jogar uma peca se ela corresponder a uma das extremidades abertas do conjunto de pecas no centro \nda mesa. Ou seja, se na mesa tiver uma peca [6|6], e possivel jogar qualquer outra peca com um 6. Suponhamos que \nfoi jogado a peca [6|4], e a mesa agora e [6|6] [6|4], nessa situacao e possivel jogar qualquer peca com 6 ou 4. \nSe um jogador nao tiver uma peca para jogar, ele deve passar a sua vez.\n\n");
	printf("  Os jogadores vao alternando rodadas ate que um jogador tenha jogado todas as suas pecas, vencendo a rodada, ou \nate que nao haja mais movimentos possiveis, resultando em um empate.\n");
	printf("\n================================================================================================================\n");
}

void apresentamensagem(char mens[100])
{
	printf("%s\n", mens);
}