#include "JogadorHumano.h"

#include <iostream>
using namespace std;
#include "utils.h"

JogadorHumano::JogadorHumano(cor time, Estado &estado) : Jogador(time,HUMANO,estado) {}

JogadorHumano::~JogadorHumano() {}

tipoEstadoJogador JogadorHumano::cliqueEsquerdo( casa casaClicada, Ponto pos )
{
	casa minhaPeca = meuTime==BRANCO ? PCBRANCA : PCPRETA;

	switch( estado )
	{
		case PARADO: 
			if( casaClicada==minhaPeca ) //selecionou uma peca válida
			{
				pecaSelecionada = pos;
				estado = SELECIONADO;
				return SELECIONADO;
			}
			else
				return PARADO;
			break;
			
		case SELECIONADO:
			if( casaClicada==minhaPeca && pos==pecaSelecionada )
			{
				estado = PARADO;
				return PARADO;
			} 
			else if( casaClicada==NADA )
			{	
				jogadaDecidida = Jogada(pecaSelecionada,pos);
				
				vector<Jogada> jogadasPossiveis = estadoJogo.getJogadasPossiveis(meuTime);
				
				for(unsigned int i=0; i<jogadasPossiveis.size(); i++)
					if( jogadasPossiveis[i] == jogadaDecidida )
					{
						estado = DECIDIU;
						return estado;
					}
					
				estado = SELECIONADO;
				return estado;
			}			
			break;
			
		case DECIDIU:
			return DECIDIU;
			break;
	}	

}

Estado JogadorHumano::retornaJogada()
{
	return estadoJogo.movePeca(jogadaDecidida.first,jogadaDecidida.second).first;
}

tipoEstadoJogador JogadorHumano::cliqueDireito( Ponto clicado )
{
	estado = PARADO;
}
