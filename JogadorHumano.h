#pragma once

#include "Jogador.h"

class JogadorHumano : public Jogador
{
	public:
		JogadorHumano(cor time, Estado &estado);
		~JogadorHumano();

		// atributos
		tipoEstadoJogador	estado;
		Ponto				pecaSelecionada;
		
		// funções
		Estado				retornaJogada();
		tipoEstadoJogador	cliqueEsquerdo( casa peca, Ponto pos );
		tipoEstadoJogador	cliqueDireito( Ponto clicado );
		
	private:
		Jogada				jogadaDecidida;
	
	
};
