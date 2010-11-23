#pragma once

#include "Estado.h"
#include "constantes.h"


class Jogador
{
	public:
		Jogador(cor time, tipoJogador tipo, Estado &estadoAtual );
		~Jogador();
		
		tipoJogador		tipo;
		cor 			meuTime;

		void 			setaEstadoAtual(Estado &estadoAtual);
		virtual Estado 	retornaJogada() = 0;
	protected:
		Estado& 		estadoJogo;
};
