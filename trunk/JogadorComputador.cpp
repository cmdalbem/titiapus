#include "JogadorComputador.h"


JogadorComputador::JogadorComputador() : Jogador(), maxProfundidade(8) {}
JogadorComputador::JogadorComputador(const Estado& estado, cor time) : Jogador(estado, time), maxProfundidade(8) {}

JogadorComputador::JogadorComputador( cor time )
{
	tipo = COMPUTADOR;
	meuTime = time;
}

JogadorComputador::~JogadorComputador() {}

Jogada JogadorComputador::retornaJogada( vector<Jogada> jogadasPossiveis )
{
    //srand(time(0));
    vector<Jogada> jogadasObrigatorias = estadoJogo.jogadasObrigatorias(meuTime);

	if(jogadasObrigatorias.size()>0)
		return jogadasObrigatorias[0];//[rand()%jogadasObrigatorias.size()];
	else
	{
		const vector<Estado> sucessores = estadoJogo.listaSucessores(meuTime);
		const vector<Jogada> jogadas = estadoJogo.listaPossibilidades(meuTime);

		float max = -9999999;
		int maxDecisao = 0;

		for (unsigned int i = 0; i < sucessores.size(); ++i)
		{
			float newMax = minimax(sucessores[i], -9999999, 9999999 , maxProfundidade-1, meuTime == BRANCO? PRETO : BRANCO);
			if (newMax > max) {
				max = newMax;
				maxDecisao = i;
			}
		}

		return jogadas[maxDecisao];
	}
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
	if(estado.npecas[cor_inimiga] != 0)
		util =  (float)estado.npecas[cor_time]/estado.npecas[cor_inimiga];
	else
		util = 1000;

    /*
    estado.print();
    printf("\nUtilidade do Jogador %s:%f\n----------\n", cor_time == BRANCO? "Branco" : "Preto",util);
    */
    return util;
}
