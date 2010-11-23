#pragma once

#include "Jogador.h"

class JogadorComputador : public Jogador
{
	public:
		JogadorComputador(cor time, Estado &estado, int minimax);
		~JogadorComputador();

		Estado 	        retornaJogada();
	
	private:
		static float    minimax(const Estado& inicial, float alfa, float beta, int _profundidade, cor _meuTime);
		static float 	utilidade(Estado estado, cor cor_time);

   		int 			maxProfundidade;
};
