//DOM-ACER-controller.cpp - Projeto Dominó 
//13/09/2023
//Grupo: ACER
//André Garrido Macedo, Caroline Guimarães Campos, Emili Vieira Tabuti, Rafael de Mello Turaça

#include"DOM-ACER-controller.h"
#include"DOM-ACER-View.cpp"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

          
          
void finiciamenu()
{
	int opc;
	do
	{
	opc = fmenu();
	switch(opc)
	{
		case 0:
			{
				break;
			}
		case 1:
			{
				fjogar();
				break;
			}
		case 2:
			{
				fregras();
				continue;
			}
		case 3:
			{
				fretomar();
				break;
			}
		case 4:
			{
				fsalvar();
				break;
			}
		case 5:
			{
				frecuperar();
				fretomar();
				break;
			}
		default: 
			{
			system("cls");	
			apresentamensagem("opcao invalida");
			continue;
			}
	}
	}while(opc != 0);

	
}       
          
          
void fcriartabuleiro() 
{
	int i, j , x;
	for(i=0 ; i <= 6 ; i++)
		{
		for(j = i ; j<=6 ; j++)
			{
				peca[x].lado1 = i ; 
				peca[x].lado2 = j ; 
				peca[x].status = '0';
				x++;
			}
		}	
}


void fembaralhar()
{
	srand(time(NULL));
	int x, y;
	for(x = 27; x >= 0  ; x--)
	{	
		y = rand() % 28 ; 
		guardapeca = peca[y];
		peca[y] = peca[x];
		peca[x] = guardapeca;
	}
}

void finicio()
{
	int i;
	int pos = -1;
	int cont = 0;
	int maiorpeca = 0; 
	for(i = 0; i <= 13 ; i ++)
	{
		if(peca[i].lado1 == peca[i].lado2)
			{
				if(peca[i].lado1 > maiorpeca)
					{
					maiorpeca = peca[i].lado1;
					pos = i;
					}
			}
	}

	
	if(pos == -1)
		{	
			for(i = 0; i <= 13 ; i ++)
			{
				if(peca[i].lado1 != peca[i].lado2)
					{
						if(peca[i].lado1 + peca[i].lado2 > maiorpeca)
							{
								maiorpeca = peca[i].lado1 + peca[i].lado2;
								pos = i;
							}
						else if(peca[i].lado1 + peca[i].lado2 == maiorpeca)
							{
								if(((peca[i].lado1 >  peca[pos].lado1)&&(peca[i].lado1 > peca[pos].lado2))||((peca[i].lado2 > peca[pos].lado1)&&(peca[i].lado2 > peca[pos].lado2)))
								{
									maiorpeca = peca[i].lado1 + peca[i].lado2;
									pos = i;
								}
							}
					
					}
			}
		}
	jvez = peca[pos].status;
	peca[pos].status = 'm'; 
	mesa[0].ladoE = peca[pos].lado1;
	mesa[0].ladoD = peca[pos].lado2;
	mesaE = peca[pos].lado1;
	mesaD = peca[pos].lado2;
	if(jvez == '1')
		{
		apresentamensagem("a primeira jogada foi do jogador 1");
		jvez = '2';
		}
	else
		{
		apresentamensagem("a primeira jogada foi do jogador 2");
		jvez = '1';
		}
	qtmesa = 1;
}

void fdistribuirpecas()
{
	int x;
	for (x = 0; x <= 6; x++)
		{
			peca[x].status = '1';
		}
	for (x = 7; x <= 13; x++)
		{	
			peca[x].status = '2';
		}
}

int comprar()
{
	int cont = 0;
	int i = 14; //as 14 primeiras peças já não estão mais livres
	do
	{
		if (peca[i].status == '0')
		{
			cont++;
			peca[i].status = jvez;
		}
		i++;
	}while((i < 28)&&(cont == 0));
	
	
	if (i >= 28)
	{
		apresentamensagem("Nada a comprar\n");
		return 0;
	}
		
	return 1; 
}

int fjogar()
{
	fembaralhar();
	fdistribuirpecas();
	system("cls");
	qntd = qntdjogadores();
	if(qntd == 2)
	{
		finicio();
		int cont = 0;
		int z = 0 ; 
		do
		{
			z = finiciamenu2();
			if(z == -1)
				{
					break;
					return -1;
				}
		}while(z != -1);
	}
	else if(qntd == 1)
	{
		finicio();
		int cont = 0;
		int z = 0 ; 
		
		if(jvez == '1')
		{
		do
		{
			z = finiciamenu2();
			z = fcomputador();
			int vencedor , empate;
			vencedor = fvencedor();
			if(vencedor == 0)
				{
					if(jvez == '1')
						apresentamensagem("Jogador 2 venceu!");
					else 
						apresentamensagem("Jogador 1 venceu!");
					qtmesa = 0 ;
					return -1;	
				}
			empate = fempate();
			if(empate == 0)
				{
					int i, pts1 , pts2, qtd1 , qtd2;
					pts1 = 0; pts2 = 0; qtd1 = 0 ; qtd2 = 0 ; 
					for(i = 0; i < 28; i++)
					{
						if(peca[i].status == '1')
						{
							qtd1++;
							pts1 = pts1 + peca[i].lado1 + peca[i].lado2 ;
						}
						else if(peca[i].status == '2')
						{
							qtd2++ ;
							pts2 = pts2 + peca[i].lado1 + peca[i].lado2 ;
						}
					}
					if(qtd1 < qtd2)
						apresentamensagem("jogador 1 venceu por ter menos pecas");
					else if(qtd2 < qtd1)
						apresentamensagem("jogador 2 venceu por ter menos pecas");
					else if(qtd1 == qtd2)
					{
					if(pts1 < pts2)
						apresentamensagem("jogador 1 venceu por ter menos pontos");
					else if(pts2 < pts1)
						apresentamensagem("jogador 2 venceu por ter menos pontos");
					else
						apresentamensagem("empate");
					}
					qtmesa = 0;
					return -1;
				}	
			if(z == -1)
				{
					break;
					return -1;
				}
				
		}while(z != -1);
		}
		
		else if(jvez == '2')
		{
		do
		{
			z = fcomputador();
			int vencedor, empate ; 
			vencedor = fvencedor();
			if(vencedor == 0)
				{
					if(jvez == '1')
						apresentamensagem("Jogador 2 venceu!");
					else 
						apresentamensagem("Jogador 1 venceu!");
					return -1;
					qtmesa = 0 ;
				}
			empate = fempate();
			if(empate == 0)
				{
					int i, pts1 , pts2, qtd1 , qtd2;
					pts1 = 0; pts2 = 0; qtd1 = 0 ; qtd2 = 0 ; 
					for(i = 0; i < 28; i++)
					{
						if(peca[i].status == '1')
						{
							qtd1++;
							pts1 = pts1 + peca[i].lado1 + peca[i].lado2 ;
						}
						else if(peca[i].status == '2')
						{
							qtd2++ ;
							pts2 = pts2 + peca[i].lado1 + peca[i].lado2 ;
						}
					}
					if(qtd1 < qtd2)
						apresentamensagem("jogador 1 venceu por ter menos pecas");
					else if(qtd2 < qtd1)
						apresentamensagem("jogador 2 venceu por ter menos pecas");
					else if(qtd1 == qtd2)
					{
					if(pts1 < pts2)
						apresentamensagem("jogador 1 venceu por ter menos pontos");
					else if(pts2 < pts1)
						apresentamensagem("jogador 2 venceu por ter menos pontos");
					else
						apresentamensagem("empate");
					}
					qtmesa = 0;
					return -1;
				}
			z = finiciamenu2();
			if(z == -1)
				{
				break;
				return -1;
				}
		}while(z != -1);
		}
	}
	return 0;
}

int finiciamenu2()
{
	int op;
	do
	{
	op = apresentamenu2();
	switch(op)
	{	
	
		case 1:
			{
				flush_in();
				fvalidarpeca(fjogapeca());
				int vencedor , empate;
				vencedor = fvencedor();
				if(vencedor == 0)
				{
					if(jvez == '1')
						apresentamensagem("Jogador 2 venceu!");
					else 
						apresentamensagem("Jogador 1 venceu!");
					qtmesa = 0 ;
					return -1;
				}
				empate = fempate();
				if(empate == 0)
				{
					int i, pts1 , pts2, qtd1 , qtd2;
					pts1 = 0; pts2 = 0; qtd1 = 0 ; qtd2 = 0 ; 
					for(i = 0; i < 28; i++)
					{
						if(peca[i].status == '1')
						{
							qtd1++;
							pts1 = pts1 + peca[i].lado1 + peca[i].lado2 ;
						}
						else if(peca[i].status == '2')
						{
							qtd2++ ;
							pts2 = pts2 + peca[i].lado1 + peca[i].lado2 ;
						}
					}
					if(qtd1 < qtd2)
						apresentamensagem("jogador 1 venceu por ter menos pecas");
					else if(qtd2 < qtd1)
						apresentamensagem("jogador 2 venceu por ter menos pecas");
					else if(qtd1 == qtd2)
					{
					if(pts1 < pts2)
						apresentamensagem("jogador 1 venceu por ter menos pontos");
					else if(pts2 < pts1)
						apresentamensagem("jogador 2 venceu por ter menos pontos");
					else
						apresentamensagem("empate");
					}
				
					qtmesa = 0;	
					return -1;
				}
				return 0;
				//break;
			}
		case 2:
			{
				flush_in();
				comprar();
				break ; 
			}
		case 3:
			{
				flush_in();
				passar();
				return 0;
				//break;
			}	     
		case 0:
			{
				apresentamensagem("jogo pausado");
				return -1 ; 
			}
		default:
			{
				apresentamensagem("opcao invalida\n");
				break;
			}
	}
	}while(op != 0);
	return 0 ; 
}

int passar()
{
	int i = 14; 
	while(i < 28)
	{
		if(peca[i].status == '0')
			{
				apresentamensagem("ainda existem pecas para comprar");
				return 0;
			}
		i++;
	}
	int j = 0; 
	while(j < 28)
	{
		if(peca[j].status == jvez)
		{
		if(((peca[j].lado1 == mesaE )||(peca[j].lado1 == mesaD)||(peca[j].lado2 == mesaE )||(peca[j].lado2 == mesaD)))
			{
			apresentamensagem("ainda existem pecas para jogar");
			return 0;
			}
		}
		j++;	
	}
	
	if ((j >= 28)&&(i >= 28))
	{
		mudarjogador();
		apresentamensagem("passando turno");
	}
	
	return 1; 
}
		
void carregaMesaE(int pecajogador)
{
	for(int i = qtmesa; i > 0; i--)
		mesa[i] = mesa[i-1];

	if (peca[pecajogador].lado2 == mesaE)
 	{
 		mesa[0].ladoE = peca[pecajogador].lado1;
 		mesa[0].ladoD = peca[pecajogador].lado2;
 	}
	else
	{
		mesa[0].ladoE = peca[pecajogador].lado2;	
		mesa[0].ladoD = peca[pecajogador].lado1;
	}
	mesaE = mesa[0].ladoE;
	qtmesa++; 
	peca[pecajogador].status = 'm'; 

	mudarjogador();
}	
		
void carregaMesaD(int pecajogador)
{
	if (peca[pecajogador].lado2 == mesaD)
 	{
 		mesa[qtmesa].ladoE = peca[pecajogador].lado2;
 		mesa[qtmesa].ladoD = peca[pecajogador].lado1;
 	}
	else
	{
		mesa[qtmesa].ladoE = peca[pecajogador].lado1;	
		mesa[qtmesa].ladoD = peca[pecajogador].lado2;
	}
	mesaD = mesa[qtmesa].ladoD;
	qtmesa++; 
	peca[pecajogador].status = 'm';
	mudarjogador();
}
		
int fvalidarpeca(char op)
{
	int i;
	int posicao = -1;
	for(i = 0; i <= 25; i++)
	{
		if((alfabeto[i] == op))
			posicao = i;
	}
	if(posicao == -1)
		{
			apresentamensagem("Letra invalida\n");
			return posicao; 
		}
	else
	{
	int j , k;
	k = -1;
	
	for(j = 0 ; j < 28; j++)
		{
			if(peca[j].status == jvez)
				k++;	
			if(k == posicao)
				break;
		}
	
	if((k == -1)||(peca[j].status != jvez))
	{
		apresentamensagem("A peca nao e valida\n");
		return -1;
	}
	
	if((mesaD == mesaE))
		{
			if((peca[j].lado1 == mesaE)||(peca[j].lado2 == mesaE))
			{
			
			int lado;
			lado = escolherLado();
			switch(lado)
				{
					case 'E':
						carregaMesaE(j);
						break;
					case 'D':
						carregaMesaD(j);
						break;
					default:
						apresentamensagem("lado invalido");
						break;
				}
			}
		}
		else if(mesaE != mesaD)
			{
				if(peca[j].lado1 == peca[j].lado2)
				{
					if(peca[j].lado1 == mesaE)
						{
							carregaMesaE(j);
						}
					else if(peca[j].lado1 == mesaD)
						{
							carregaMesaD(j);
						}
				}
				else if(((peca[j].lado1 == mesaE)||(peca[j].lado1 == mesaD))&&((peca[j].lado2 == mesaE)||(peca[j].lado2 == mesaD)))
					{
						int lado;
						lado = escolherLado();
						switch(lado)
						{ 
						case 'E':
							carregaMesaE(j);
							break;
						case 'D':
							carregaMesaD(j);
							break;
						default:
							apresentamensagem("lado invalido");
							break;
						}
					}
				else if(((peca[j].lado1 == mesaD )||(peca[j].lado2 == mesaD)))
					carregaMesaD(j);
				else if(((peca[j].lado1 == mesaE )||(peca[j].lado2 == mesaE)))
					carregaMesaE(j);
			}
		
		else
		{
			apresentamensagem("a peca nao e valida");
		}
	return 0;
	}
}

void mudarjogador()
{
	if(jvez == '1')
		{
			jvez = '2';
			system("cls");
			apresentamensagem("Vez do jogador 2");
		}
		else
		{
			jvez = '1';
			system("cls");
			apresentamensagem("Vez do jogador 1");
		}
}
void flush_in() //ou void fclear()
{
	int ch;
	while( (ch = fgetc(stdin)) != EOF && ch != '\n');
}


void fretomar()
{
	if(qtmesa == 0)
		apresentamensagem("Nao existe um jogo iniciado");
	else
		finiciamenu2();
}


int fvencedor()
{
	int i;
	if(jvez == '1')
	{
	for(i = 0 ; i < 28 ; i++)
		{
			if(peca[i].status == '2')
				return 1;
		}
		return 0;
	}		
	else
	{
		for(i = 0 ; i < 28 ; i++)
		{
			if(peca[i].status == '1')
				return 1;
		}
		return 0;
	}
	
}

int fempate()
{
	int i, j;
	for(j = 0; j < 28 ; j++)
	{
		if(peca[j].status == '0')
			return 1;
	}
	for(i = 0; i < 28 ; i++)
	{
		{
		if(((peca[i].status == '1')||(peca[i].status == '2'))&&((peca[i].lado1 == mesaE)||(peca[i].lado1 == mesaD)||(peca[i].lado2 == mesaE)||(peca[i].lado2 == mesaD)))
			return 1;
		}
	}
	return 0; 
}

void fsalvar()
{
	int i;
	FILE *fp;
	FILE *fpm;
	FILE *fps;
	
	sitJogo.qtmesaJogo = qtmesa; 
	sitJogo.mesaDJogo = mesaD;
	sitJogo.mesaDJogo = mesaE;
	sitJogo.jogadorJogo = jvez;
	sitJogo.jogadorComp = qntd;
	
	if(qtmesa == 0)
		{
			apresentamensagem("Sem jogo a ser gravado");
			return;
		}
	
	if((fp = fopen("CAD_DOMINO", "w")) == NULL)
		{
			apresentamensagem("O arquivo CAD_DOMINO nao pode ser aberto para cadastrar");
			return;	
		}
	if((fpm = fopen("CAD_MESA", "w")) == NULL)
		{
			apresentamensagem("O arquivo CAD_MESA nao pode ser aberto para cadastrar");
			return;
		}
	if((fps = fopen("CAD_JOGO", "w")) == NULL)
		{
			apresentamensagem("O arquivo CAD_JOGO nao pode ser aberto para cadastrar");
			return;
		}

	for(i = 0; i < 28; i++)
		{
			if (fwrite(&peca[i], sizeof(struct stpeca), 1, fp) != 1)
				{
					apresentamensagem("Erro na gravacao do arquivo CAD_DOMINO");
					break;
				}
		}
	
	for(i = 0; i < 28; i++)
		{
			if(fwrite(&mesa[i], sizeof(struct Mesa), 1, fpm) != 1)
				{
					apresentamensagem("Erro na gravacao do arquivo CAD_MESA");
					break;
				}
		}
	
	if (fwrite(&sitJogo, sizeof(struct Jogo), 1, fps) != 1)
 		apresentamensagem("Erro na gravacao do arquivo CAD_JOGO");
	
	fclose(fps);
	fclose(fpm);
	fclose(fp);
	apresentamensagem("Gravados os arquivos CAD_DOMINO, CAD_MESA e CAD_JOGO");
}

void frecuperar()
{
	
	int i;
	FILE *fp;
	FILE *fpm;
	FILE *fps;

	if((fp = fopen("CAD_DOMINO", "r")) == NULL)
	{
		apresentamensagem("O arquivo CAD_DOMINO nao pode ser aberto");
		return;
	}
	if((fpm = fopen("CAD_MESA", "r")) == NULL)
	{
		apresentamensagem("O arquivo CAD_MESA nao pode ser aberto");
		return;
	}
	if((fps = fopen("CAD_JOGO", "r")) == NULL)
	{
		apresentamensagem("O arquivo CAD_JOGO nao pode ser aberto");
		return;
	}
	for(i = 0; i < 28; i++)
	{
		if (fread(&peca[i], sizeof(struct stpeca), 1, fp) != 1)
		{
			apresentamensagem("Erro na leitura do arquivo CAD_DOMINO");
			break;
		}
	}
	for(i = 0; i < 28; i++)
	{
		if (fread(&mesa[i], sizeof(struct Mesa), 1, fpm) != 1)
		{
			apresentamensagem("Erro na leitura do arquivo CAD_MESA");
			break;
		}
	}
	if (fread(&sitJogo, sizeof(struct Jogo), 1, fps) != 1) 
		apresentamensagem("Erro na leitura do arquivo CAD_JOGO");
		
	fclose(fps);
	fclose(fpm);
	fclose(fp);

	qtmesa = sitJogo.qtmesaJogo;
	jvez = sitJogo.jogadorJogo;
	qntd = sitJogo.jogadorComp;
	mesaD = sitJogo.mesaDJogo;
	mesaE = sitJogo.mesaEJogo;
	apresentamensagem("retornando ao jogo recuperado");
	
	
}

int fcomputador()
{
	int i, w; 
	int j = 0;	
	
	do
	{
	for(i = 0 ; i < 28 ; i++)
	{
		if(peca[i].status == '2')
			{
				if((peca[i].lado1 == mesaE)||(peca[i].lado2 == mesaE))
						{
						j++;
						carregaMesaE(i);
						return 0;
						}
				else if((peca[i].lado1 == mesaD)||(peca[i].lado2 == mesaD))
						{
						j++;
						carregaMesaD(i);
						return 0;
						}
			}
	}
		if(j == 0)
		{
			int x;
			x = comprar();
			if(x == 0)  
				{
				passar();
				return 0;
				}
			else
				w = 1;
		}
	}while(w == 1);
}
	