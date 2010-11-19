
#include "IA.h"
#include "constantes.h"
#include "Estado.h"

#include <stdlib.h>
#include <time.h>

#include <map>
#include <iostream>
using namespace std;


IA::IA( int _profundidade, Estado _estado, cor _meu_time )
{
	profundidade = _profundidade;
	estado = _estado;
	meu_time = _meu_time;
}

IA::IA( int _profundidade, Estado _estado, cor _meu_time, vector< Jogada > _jogadasObrigatorias )
{
	profundidade = _profundidade;
	estado = _estado;
	meu_time = _meu_time;
	jogadasObrigatorias = _jogadasObrigatorias;
}

float IA::minimax(Estado inicial, int _profundidade, float alfa, float beta, cor cor_time)
{
	if ( _profundidade == 0)
	{ //should test if is leaf, but nah :)
		return IA::utilidade(inicial, cor_time);
	}
	else
	{
		vector<Estado> filhos = inicial.listaSucessores(cor_time);
	
		for (unsigned int i=0; i < filhos.size(); ++i)
		{
			alfa = max(alfa, - minimax(filhos[i], _profundidade-1, -beta, -alfa, cor_time == BRANCO? PRETO : BRANCO) );
			if (beta <= alfa)
				break;
		}
		return alfa;
	}
}

pair<Ponto, Ponto> IA::decideJogada()
{
	srand(time(0));
	if(jogadasObrigatorias.size()>0)
		return jogadasObrigatorias[rand()%jogadasObrigatorias.size()];
	else
	{
		const vector<Estado> sucessores = estado.listaSucessores(meu_time);
		const vector< Jogada > jogadas = estado.listaPossibilidades(meu_time);

		float max = -9999999;
		int maxDecisao = 0;

		for (unsigned int i = 0; i < sucessores.size(); ++i)
		{
			float newMax = minimax(sucessores[i], profundidade-1, -9999999, 9999999 , meu_time == BRANCO? PRETO : BRANCO);
			if (newMax > max) {
				max = newMax;
				maxDecisao = i;
			}
		}

		return jogadas[maxDecisao];
	}
}

float IA::utilidade(Estado estado, cor cor_time)
{
	cor cor_inimiga = cor_time==BRANCO? PRETO : BRANCO;
	if(estado.npecas[cor_inimiga] != 0)
		return estado.npecas[cor_time]/estado.npecas[cor_inimiga];
	else
		return 1000;
}
