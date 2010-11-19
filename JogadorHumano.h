#pragma once

#include "Jogador.h"




class JogadorHumano : public Jogador
{
	public:
		JogadorHumano(cor time);
		~JogadorHumano();

		// atributos
		tipoEstadoJogador	estado;
		Ponto				pecaSelecionada;
		
		// funções
		Jogada				retornaJogada( vector<Jogada> jogadasPossiveis );
		tipoEstadoJogador	cliqueEsquerdo( casa peca, Ponto pos );
		tipoEstadoJogador	cliqueDireito( Ponto clicado );
		
	private:
		Jogada				jogadaDecidida;
	
	
};
