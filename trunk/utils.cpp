#include "utils.h"

#include "constantes.h"

#include "math.h"
#include <vector>
#include <stdio.h>
using namespace std;


float distanciaPontos( Ponto a, Ponto b )
{
	return sqrt( pow((a.first - b.first),2) + pow((a.second - b.second),2) );
}

bool estaContido( Ponto pto, vector<Ponto> ptos )
{
	for(unsigned int i=0; i<ptos.size(); i++)
		if(ptos[i]==pto)
			return true;
	return false;
}

bool estaDentroCampo(int i, int j)
{
	return ((i < NLIN) &&
	  (i >= 0) &&
	  (j < NCOL) &&
	  (j >= 0) );
}

void printJogadas( vector<Jogada> j )
{
	printf("Lista de jogadas:\n");
	for(int i=0; i<j.size(); i++)
		printf("::(%i,%i)->(%i,%i)\n",j[i].first.first,j[i].first.second,j[i].second.first, j[i].second.second);
}
