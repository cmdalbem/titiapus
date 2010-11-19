#include "JogadorHumano.h"

JogadorHumano::JogadorHumano(cor time)
{
	tipo = HUMANO;
	meuTime = time;
}

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
			break;
			
		case SELECIONADO:
			if( casaClicada==minhaPeca && pos==pecaSelecionada )
			{
				estado = PARADO;
				return PARADO;
			} 
			else if( casaClicada==NADA )
			{
				/*
				for(unsigned int i=0; i<jogadasPossiveis.size(); i++)
					if( jogadasPossiveis[i].first == pecaSelecionada &&
						jogadasPossiveis[i].second == pos )
					{
						jogadaDecidida = jogadasPossiveis[i];
						return DECIDIU;
					}
				
				return SELECIONADO;*/
				
				jogadaDecidida = Jogada(pecaSelecionada,pos);
				return DECIDIU;
			}			
			break;
			
		case DECIDIU:
			return DECIDIU;
			break;
	}	

}

Jogada JogadorHumano::retornaJogada( vector<Jogada> _jogadasPossiveis )
{
	vector<Jogada> jogadasPossiveis = _jogadasPossiveis;
	
	for(unsigned int i=0; i<jogadasPossiveis.size(); i++)
		if( jogadasPossiveis[i] == jogadaDecidida )
			return jogadaDecidida;
	
	estado = SELECIONADO;
	return Jogada(Ponto(-1,-1),Ponto(-1,-1));
}

tipoEstadoJogador JogadorHumano::cliqueDireito( Ponto clicado )
{
	estado = PARADO;
}
