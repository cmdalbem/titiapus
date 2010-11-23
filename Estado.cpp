#include <vector>
#include <stdio.h>

#include "Estado.h"


casa Linha::operator[] (int index) const
{
	if(index < 0 || index >= NCOL) return NADA;

	u_int16 aux = _linha;
	aux >>= 2*index;
	return (casa) (aux & 0x0003);
}

void Linha::set(int index, casa valor)
{
	if(index < 0 || index >= NCOL) return;
	u_int16 val16 = (u_int16)valor;
	if( val16 > 0x02) return;

	u_int16 mask = 0x0003;

    val16 <<= 2*index;
    mask <<= 2*index;

	mask = ~mask;

	_linha = (_linha & mask) | val16;
}

void Linha::limpaReservadas()
{
    for(u_int16 mask = 0x3000; mask != 0; mask = mask >> 2)
        if((_linha & mask) == mask)
            _linha = _linha & !mask;
}

//---------------------------------------

Estado::Estado() {};

Estado::Estado(const Estado & _estado)
{
	*this = _estado;
}

Estado::~Estado() {};

void Estado::setaCasa(int x, int y, casa valor)
{
    pecas[x].set(y, valor);
}

void Estado::limpaReservadas()
{
     for(int lin = 0; lin < NLIN; lin++)
        pecas[lin].limpaReservadas();
}

vector<Jogada> Estado::listaPossibilidades( Ponto peca ) const
{
	vector<Jogada> resultado;
	int i=peca.first, j=peca.second;

	// teste sem diagonais
	// int var=i+1; //refatoracao
	if( estaDentroCampo(i+1,j) && pecas[i+1][j] == NADA )
		resultado.push_back( Jogada(peca,Ponto(i+1,j)) );
	if( estaDentroCampo(i-1,j) && pecas[i-1][j] == NADA )
		resultado.push_back( Jogada(peca,Ponto(i-1,j)) );
	if(	estaDentroCampo(i,j+1) && pecas[i][j+1] == NADA )
		resultado.push_back( Jogada(peca,Ponto(i,j+1)) );
	if(	estaDentroCampo(i,j-1) && pecas[i][j-1] == NADA )
		resultado.push_back( Jogada(peca,Ponto(i,j-1)) );

	if( (i+j)%2 != 0 ) //soma das componentes é ímpar? = casa tem diagonais?
	{
		if( estaDentroCampo(i+1,j+1) && pecas[i+1][j+1] == NADA )
			resultado.push_back( Jogada(peca,Ponto(i+1,j+1)) );
		if( estaDentroCampo(i-1,j-1) && pecas[i-1][j-1] == NADA )
			resultado.push_back( Jogada(peca,Ponto(i-1,j-1)) );
		if(	estaDentroCampo(i-1,j+1) && pecas[i-1][j+1] == NADA )
			resultado.push_back( Jogada(peca,Ponto(i-1,j+1)) );
		if(	estaDentroCampo(i+1,j-1) && pecas[i+1][j-1] == NADA )
			resultado.push_back( Jogada(peca,Ponto(i+1,j-1)) );
	}


	return resultado;
}

vector<Estado> Estado::listaSucessores( Ponto peca ) const
{
	vector<Estado> sucessores;
	vector<Jogada> jogadas = listaPossibilidades(peca);


	for(unsigned int jog = 0; jog < jogadas.size() ; jog++)
		sucessores.push_back( movePeca( peca, jogadas[jog].second ).first );

	return sucessores;
}

pair<Estado,bool> Estado::movePeca( Ponto origem, Ponto destino ) const
{
	Estado novo_estado(*this);

	casa peca_movida = novo_estado.pecas[origem.first][origem.second];
	novo_estado.setaCasa(origem.first, origem.second, NADA);
	novo_estado.setaCasa(destino.first, destino.second, peca_movida);
	casa peca_inimiga = (peca_movida == PCBRANCA)? PCPRETA : PCBRANCA;
	Ponto direcao(destino.first - origem.first, destino.second - origem.second); // Direção da peça
	Ponto adjacente(destino.first + direcao.first, destino.second + direcao.second);
	cor cor_peca_inimiga = (peca_inimiga == PCBRANCA)? BRANCO : PRETO;
	bool comeu_peca = false;

	while( estaDentroCampo(adjacente.first,adjacente.second) && novo_estado.pecas[adjacente.first][adjacente.second] == peca_inimiga )
	{
		novo_estado.setaCasa(adjacente.first, adjacente.second, NADA);
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
				vector<Jogada> jogadas = listaPossibilidades( Ponto(i,j) );

				for(unsigned int k = 0; k < jogadas.size() ; ++k)
					pares_jogadas.push_back(jogadas[k]);
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


vector< Jogada > Estado::jogadasObrigatorias( cor cor_pecas ) const
{
	vector< Jogada > jogadas = listaPossibilidades(cor_pecas);
	vector< Jogada > comComilanca;

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
	vector< Jogada > jogadas = listaPossibilidades( peca );
	vector< Jogada > comComilanca;

	for(unsigned int i = 0 ; i < jogadas.size() ; ++i)
	{
		pair<Estado,bool> move_sem_nome = movePeca(peca, jogadas[i].second);
		if( move_sem_nome.second ) //ou seja, há comilança de peças
			comComilanca.push_back( jogadas[i] );
	}

	return comComilanca;
}

void Estado::print() const
{
    for(int i = 0; i < NLIN; i++)
    {
        for(int j = 0; j < NCOL; j++)
            printf("%d", pecas[i][j]);
        printf("\n");
    }
    printf("Pecas Brancas: %d\nPecas Pretas: %d\n", npecas[BRANCO], npecas[PRETO]);
}
