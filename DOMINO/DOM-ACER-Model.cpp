//DOM-ACER-Model.cpp - Projeto Dominó
//13/09/2023
//Grupo: ACER
//André Garrido Macedo, Caroline Guimarães Campos, Emili Vieira Tabuti, Rafael de Mello Turaça

#include "DOM-ACER-Model.h"

typedef struct stpeca
	{
		int lado1;
		int lado2;
		char status;
	}tipoPeca;

struct Mesa
{
	int ladoE;
	int ladoD;	
}mesa[28];

tipoPeca peca[28];
tipoPeca guardapeca;

struct Jogo
{
	int qtmesaJogo;
	int jogadorJogo; 
	int jogadorComp; 
	int mesaDJogo; 
	int mesaEJogo; 
} sitJogo; 


