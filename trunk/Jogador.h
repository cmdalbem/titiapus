#pragma once

#include "Estado.h"
#include "constantes.h"


class Jogador
{
	public:
		Jogador(cor time, tipoJogador tipo );
		~Jogador();
		
		tipoJogador		tipo;
		cor 			meuTime;

		void 			setaEstadoAtual(const Estado& estadoAtual);
		virtual Jogada 	retornaJogada( vector<Jogada> jogadasPossiveis ) = 0;
	protected:
		Estado 			estadoJogo;
};
