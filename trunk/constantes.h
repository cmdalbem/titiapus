#pragma once

#include <map>
using namespace std;


#define NLIN 5
#define NCOL 7

#define FRAMEX 50
#define FRAMEY 50

#define TELAX (NCOL*100 + 2*FRAMEX)
#define TELAY (NLIN*100 + 2*FRAMEY)

#define PECA_RAIO 25


typedef pair<int,int> Ponto;
typedef pair<Ponto,Ponto> Jogada;

enum cor
{
	PRETO, BRANCO,
	TOTAL_COR
};

enum casa
{
    NADA, PCBRANCA, PCPRETA,
    TOTAL_CASA
};

enum tipoJogador
{
	HUMANO, MAQUINA
};

enum tipoAcaoPendente
{
	SELECAO, ACAO
};

#define LIN(i) ((TELAY-2*FRAMEY)/((float)NLIN-1))*i + FRAMEY
#define COL(i) ((TELAX-2*FRAMEX)/((float)NCOL-1))*i + FRAMEX
#define POS(i,j) ((TELAX-2*FRAMEX)/((float)NCOL-1))*j + FRAMEX , ((TELAY-2*FRAMEY)/((float)NLIN-1))*i + FRAMEY
