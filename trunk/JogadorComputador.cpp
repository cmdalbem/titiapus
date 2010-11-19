#include "JogadorComputador.h"

JogadorComputador::JogadorComputador() {}
JogadorComputador::JogadorComputador(const Estado& estado, cor time) : Jogador(estado, time) {}
JogadorComputador::~JogadorComputador() {}

Jogada JogadorComputador::retornaJogada()
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
			float newMax = minimax(sucessores[i], maxProfundidade-1, -9999999, 9999999 , meuTime == BRANCO? PRETO : BRANCO);
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
			alfa = max(alfa, - minimax(filhos[i], _profundidade-1, -beta, -alfa, _meuTime == BRANCO? PRETO : BRANCO) );
			if (beta <= alfa)
				break;
		}
		return alfa;
	}
}

float JogadorComputador::utilidade(Estado estado, cor cor_time)
{
    cor cor_inimiga = cor_time==BRANCO? PRETO : BRANCO;
	if(estado.npecas[cor_inimiga] != 0)
		return estado.npecas[cor_time]/estado.npecas[cor_inimiga];
	else
		return 1000;
}
