#pragma once

#include "Estado.h"
#include "constantes.h"


class Jogador
{
	public:
		Jogador();
		Jogador(const Estado& estado, cor time);
		~Jogador();
		
		tipoJogador			tipo;
		cor 				meuTime;

		void 			setaEstadoAtual(const Estado& estadoAtual);
		virtual Jogada 	retornaJogada( vector<Jogada> jogadasPossiveis ) = 0;
	protected:
		Estado 			estadoJogo;
};
