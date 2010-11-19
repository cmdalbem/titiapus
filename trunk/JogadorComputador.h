#pragma once

#include "Jogador.h"

class JogadorComputador : public Jogador
{
	public:
		JogadorComputador();
		JogadorComputador(const Estado& estado, cor time);
		~JogadorComputador();

		Jogada 	        retornaJogada( vector<Jogada> jogadasPossiveis );
	private:
		static float    minimax(const Estado& inicial, float alfa, float beta, int _profundidade, cor _meuTime);
		static float 	utilidade(Estado estado, cor cor_time);

		int 			maxProfundidade;
};
