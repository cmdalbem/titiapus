#pragma once

#include "Jogador.h"


class JogadorHumano : public Jogador
{
	public:
		JogadorHumano();
		JogadorHumano(const Estado& estado, cor time);
		~JogadorHumano();

		Jogada retornaJogada( vector<Jogada> jogadasPossiveis );
		
	private:
	
	
};
