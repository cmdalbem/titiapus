#include "JogadorComputador.h"

#include <iostream>
using namespace std;


JogadorComputador::JogadorComputador(cor time, Estado &estado, int minimax) : Jogador(time,COMPUTADOR,estado), maxProfundidade(minimax) {}

JogadorComputador::~JogadorComputador() {}

Estado JogadorComputador::retornaJogada()
{
	const vector<Estado> sucessores = estadoJogo.listaSucessores(meuTime);
	
	for(int i=0;i<sucessores.size();i++)
		printJogadas(sucessores[i].ultimasJogadas);

	float max = -9999999;
	int maxDecisao = 0;
	
	cout << "PROFUNDIDADE=" << maxProfundidade;

	for (unsigned int i = 0; i < sucessores.size(); ++i)
	{
		float newMax = minimax(sucessores[i], -9999999, 9999999 , maxProfundidade-1, meuTime == BRANCO? PRETO : BRANCO);
		if (newMax > max) {
			max = newMax;
			maxDecisao = i;
		}
	}
	
	//cout << "tamanho=" << sucessores[maxDecisao].ultimasJogadas.size() << endl;
	return sucessores[maxDecisao];//.ultimasJogadas[ sucessores[maxDecisao].ultimasJogadas.size()-1 ];
}

float JogadorComputador::minimax(const Estado& atual, float alfa, float beta, int _profundidade, cor _meuTime)
{
    if ( _profundidade == 0)
	{ //should test if is leaf, but nah :)
		return JogadorComputador::utilidade(atual, _meuTime);
	}
	else
	{
		vector<Estado> filhos = atual.listaSucessores(_meuTime);

		for (unsigned int i=0; i < filhos.size(); ++i)
		{
			alfa = max(alfa, - minimax(filhos[i], -beta, -alfa, _profundidade-1, _meuTime == BRANCO? PRETO : BRANCO) );
			if (beta <= alfa)
				break;
		}
		return alfa;
	}
}

float JogadorComputador::utilidade(Estado estado, cor cor_time)
{
    cor cor_inimiga = cor_time==BRANCO? PRETO : BRANCO;

    float util = 0;

    util =  (float)estado.npecas[cor_time]/(estado.npecas[cor_time] + estado.npecas[cor_inimiga]);


    /*
    estado.print();
    printf("\nUtilidade do Jogador %s:%f\n----------\n", cor_time == BRANCO? "Branco" : "Preto",util);
    */
    return util;
}
