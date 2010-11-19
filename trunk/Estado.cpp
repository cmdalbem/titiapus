#include <vector>

#include "Estado.h"


Estado::Estado() {};

Estado::Estado(const Estado & _estado)
{
	*this = _estado;
}

Estado::~Estado() {};

vector<Ponto> Estado::listaPossibilidades( Ponto pto ) const
{
	vector<Ponto> resultado;
	int i=pto.first, j=pto.second;

	// teste sem diagonais
	// int var=i+1; //refatoracao
	if( estaDentroCampo(i+1,j) && pecas[i+1][j] == NADA )
		resultado.push_back( Ponto(i+1,j) );
	if( estaDentroCampo(i-1,j) && pecas[i-1][j] == NADA )
		resultado.push_back( Ponto(i-1,j) );
	if(	estaDentroCampo(i,j+1) && pecas[i][j+1] == NADA )
		resultado.push_back( Ponto(i,j+1) );
	if(	estaDentroCampo(i,j-1) && pecas[i][j-1] == NADA )
		resultado.push_back( Ponto(i,j-1) );

	if( (i+j)%2 != 0 ) //soma das componentes é ímpar? = casa tem diagonais?
	{
		if( estaDentroCampo(i+1,j+1) && pecas[i+1][j+1] == NADA )
			resultado.push_back( Ponto(i+1,j+1) );
		if( estaDentroCampo(i-1,j-1) && pecas[i-1][j-1] == NADA )
			resultado.push_back( Ponto(i-1,j-1) );
		if(	estaDentroCampo(i-1,j+1) && pecas[i-1][j+1] == NADA )
			resultado.push_back( Ponto(i-1,j+1) );
		if(	estaDentroCampo(i+1,j-1) && pecas[i+1][j-1] == NADA )
			resultado.push_back( Ponto(i+1,j-1) );
	}


	return resultado;
}

vector<Estado> Estado::listaSucessores( Ponto pto ) const
{
	vector<Estado> sucessores;
	vector<Ponto> jogadas = listaPossibilidades(pto);

	for(unsigned int jog = 0; jog < jogadas.size() ; jog++)
		sucessores.push_back( movePeca( pto, Ponto(jogadas[jog].first, jogadas[jog].second) ).first );

	return sucessores;
}

pair<Estado,bool> Estado::movePeca( Ponto origem, Ponto destino ) const
{
	Estado novo_estado(*this);

	casa peca_movida = novo_estado.pecas[origem.first][origem.second];
	novo_estado.pecas[origem.first][origem.second] = NADA;
	novo_estado.pecas[destino.first][destino.second] = peca_movida;
	casa peca_inimiga = (peca_movida == PCBRANCA)? PCPRETA : PCBRANCA;
	Ponto direcao(destino.first - origem.first, destino.second - origem.second); // Direção da peça
	Ponto adjacente(destino.first + direcao.first, destino.second + direcao.second);
	cor cor_peca_inimiga = (peca_inimiga == PCBRANCA)? BRANCO : PRETO;
	bool comeu_peca = false;

	while( estaDentroCampo(adjacente.first,adjacente.second) && novo_estado.pecas[adjacente.first][adjacente.second] == peca_inimiga )
	{
		novo_estado.pecas[adjacente.first][adjacente.second] = NADA;
		adjacente.first += direcao.first;
		adjacente.second += direcao.second;
		novo_estado.npecas[cor_peca_inimiga]--;
		comeu_peca = true;
	}
	return pair<Estado,bool>(novo_estado, comeu_peca);
}

vector< Jogada > Estado::listaPossibilidades( cor cor_pecas) const
{
	casa fail_code = cor_pecas == BRANCO? PCBRANCA : PCPRETA ;
	vector< Jogada > pares_jogadas;

	for(int i = 0 ; i < NLIN ; i++)
		for(int j = 0 ; j < NCOL ; j++)
			if(pecas[i][j] == fail_code)
			{
				vector<Ponto> jogadas = listaPossibilidades( Ponto(i,j) );

				for(unsigned int k = 0; k < jogadas.size() ; ++k)
				pares_jogadas.push_back(Jogada( Ponto(i,j), jogadas[k] ) );
			}

	return pares_jogadas;
}

vector<Estado> Estado::listaSucessores( cor cor_pecas ) const
{
	casa fail_code = cor_pecas == BRANCO? PCBRANCA : PCPRETA ;
	vector<Estado> sucessores_cor;

	for(int i = 0 ; i < NLIN ; i++)
		for(int j = 0 ; j < NCOL ; j++)
			if(pecas[i][j] == fail_code)
			{
				vector<Estado> sucessores_peca = listaSucessores( Ponto(i,j) );
				sucessores_cor.insert(sucessores_cor.begin(), sucessores_peca.begin(), sucessores_peca.end());
			}

	return sucessores_cor;
}


vector<Jogada> Estado::jogadasObrigatorias( cor cor_pecas ) const
{
	vector<Jogada> jogadas = listaPossibilidades(cor_pecas);
	vector<Jogada> comComilanca;

	for(unsigned int i = 0 ; i < jogadas.size() ; ++i)
	{
		pair<Estado,bool> move_sem_nome = movePeca(jogadas[i].first, jogadas[i].second);
		if( move_sem_nome.second ) //ou seja, há comilança de peças
			comComilanca.push_back( jogadas[i] );
	}

	return comComilanca;
}

vector< Jogada > Estado::jogadasObrigatorias( Ponto peca ) const
{
	vector< Ponto > jogadas = listaPossibilidades( peca );
	vector< Jogada > comComilanca;

	for(unsigned int i = 0 ; i < jogadas.size() ; ++i)
	{
		pair<Estado,bool> move_sem_nome = movePeca(peca, jogadas[i]);
		if( move_sem_nome.second ) //ou seja, há comilança de peças
			comComilanca.push_back( Jogada(peca,jogadas[i]) );
	}

	return comComilanca;
}
