#include <vector>

#include "Estado.h"
#include "utils.h"


Estado::Estado() {};

Estado::Estado(const Estado & _estado)
{
	*this = _estado;
}

Estado::~Estado() {};
				
vector<point> Estado::listaPossibilidades( int i, int j )
{
	vector<point> resultado;
	
	// teste sem diagonais
	// int var=i+1; //refatoracao
	if( estaDentroCampo(i+1,j) && pecas[i+1][j] == NADA )
		resultado.push_back( point(i+1,j) );		
	if( estaDentroCampo(i-1,j) && pecas[i-1][j] == NADA )
		resultado.push_back( point(i-1,j) );
	if(	estaDentroCampo(i,j+1) && pecas[i][j+1] == NADA )
		resultado.push_back( point(i,j+1) );
	if(	estaDentroCampo(i,j-1) && pecas[i][j-1] == NADA )
		resultado.push_back( point(i,j-1) );
		
	if( (i+j)%2 != 0 ) //soma das componentes é ímpar? = casa tem diagonais?
	{
		if( estaDentroCampo(i+1,j+1) && pecas[i+1][j+1] == NADA )
			resultado.push_back( point(i+1,j+1) );		
		if( estaDentroCampo(i-1,j-1) && pecas[i-1][j-1] == NADA )
			resultado.push_back( point(i-1,j-1) );
		if(	estaDentroCampo(i-1,j+1) && pecas[i-1][j+1] == NADA )
			resultado.push_back( point(i-1,j+1) );
		if(	estaDentroCampo(i+1,j-1) && pecas[i+1][j-1] == NADA )
			resultado.push_back( point(i+1,j-1) );
	}
	
	
	return resultado;
}

vector<Estado> Estado::listaSucessores( int i, int j )
{
	vector<Estado> sucessores;
	vector<point> jogadas = listaPossibilidades(i,j);

	for(unsigned int jog = 0; jog < jogadas.size() ; jog++)
		sucessores.push_back( movePeca( point(i,j), point(jogadas[jog].first, jogadas[jog].second) ).first );

	return sucessores;
}

pair<Estado,bool> Estado::movePeca( point origem, point destino )
{
	Estado novo_estado(*this);
	 
	casa peca_movida = novo_estado.pecas[origem.first][origem.second];
	novo_estado.pecas[origem.first][origem.second] = NADA;
	novo_estado.pecas[destino.first][destino.second] = peca_movida;
	casa peca_inimiga = (peca_movida == PCBRANCA)? PCPRETA : PCBRANCA;
	point direcao(destino.first - origem.first, destino.second - origem.second); // Direção da peça
	point adjacente(destino.first + direcao.first, destino.second + direcao.second);
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

vector< pair<point,point> > Estado::listaPossibilidades( cor cor_pecas)
{
	casa fail_code = cor_pecas == BRANCO? PCBRANCA : PCPRETA ;
	vector< pair<point,point> > pares_jogadas;

	for(int i = 0 ; i < NLIN ; i++)
		for(int j = 0 ; j < NCOL ; j++)
			if(pecas[i][j] == fail_code)
			{
				vector<point> jogadas = listaPossibilidades(i,j);
		   
				for(unsigned int k = 0; k < jogadas.size() ; ++k)
				pares_jogadas.push_back(pair<point,point>( point(i,j), jogadas[k] ) );
			}

	return pares_jogadas;
}

vector<Estado> Estado::listaSucessores( cor cor_pecas )
{
	casa fail_code = cor_pecas == BRANCO? PCBRANCA : PCPRETA ;
	vector<Estado> sucessores_cor;

	for(int i = 0 ; i < NLIN ; i++)
		for(int j = 0 ; j < NCOL ; j++)
			if(pecas[i][j] == fail_code)
			{
				vector<Estado> sucessores_peca = listaSucessores(i,j);
				sucessores_cor.insert(sucessores_cor.begin(), sucessores_peca.begin(), sucessores_peca.end());
			}

	return sucessores_cor;
}


vector< pair<point,point> > Estado::jogadasObrigatorias( cor cor_pecas )
{
	vector< pair<point,point> > jogadas = listaPossibilidades(cor_pecas);
	vector< pair<point,point> > comComilanca;
	
	for(unsigned int i = 0 ; i < jogadas.size() ; ++i)
	{
		pair<Estado,bool> move_sem_nome = movePeca(jogadas[i].first, jogadas[i].second);
		if( move_sem_nome.second ) //ou seja, há comilança de peças
			comComilanca.push_back( jogadas[i] );
	}
	
	return comComilanca;
}

vector< pair<point,point> > Estado::jogadasObrigatorias( point peca )
{
	vector< point > jogadas = listaPossibilidades(peca.first,peca.second);
	vector< pair<point,point> > comComilanca;
	
	for(unsigned int i = 0 ; i < jogadas.size() ; ++i)
	{
		pair<Estado,bool> move_sem_nome = movePeca(peca, jogadas[i]);
		if( move_sem_nome.second ) //ou seja, há comilança de peças
			comComilanca.push_back( pair<point,point>(peca,jogadas[i]) );
	}
	
	return comComilanca;
}