#include <iostream>
using namespace std;

#include "Jogo.h"


Jogo::Jogo( tipoJogador _jogadorBrancas, tipoJogador _jogadorPretas )
{
	novo( _jogadorBrancas, _jogadorPretas );
}

Jogo::~Jogo() {}

void Jogo::posicoesIniciais()
{
    for(int i=0; i<2; i++)
        for(int j=0; j<NCOL; j++)
            campo.pecas[i][j] = PCPRETA;
    
    for(int i=3; i<5; i++)
        for(int j=0; j<NCOL; j++)
            campo.pecas[i][j] = PCBRANCA;
            
    campo.pecas[2][0] = PCBRANCA;
    campo.pecas[2][1] = PCPRETA;
    campo.pecas[2][2] = PCBRANCA;
    campo.pecas[2][3] = NADA;
    campo.pecas[2][4] = PCPRETA;
    campo.pecas[2][5] = PCBRANCA;
    campo.pecas[2][6] = PCPRETA;
}

void Jogo::comecar()
{
	executarTurno();
}

void Jogo::novo( tipoJogador _jogadorBrancas, tipoJogador _jogadorPretas )
{
    posicoesIniciais();
    
    ultimasJogadas.clear();
    njogadas = 0;
    esperandoJogada = false;

    if(_jogadorBrancas == COMPUTADOR)
		jogador[BRANCO] = new JogadorComputador(BRANCO,2);
	else
		jogador[BRANCO] = new JogadorHumano(BRANCO);
		
	if(_jogadorPretas == COMPUTADOR)
		jogador[PRETO] = new JogadorComputador(PRETO,2);
	else
		jogador[PRETO] = new JogadorHumano(PRETO);
		
	jogadorAtual = jogador[BRANCO];
    
	campo.npecas[BRANCO] = campo.npecas[PRETO] = 17;
}

void Jogo::executaJogada( Jogada jogada )
{
	esperandoJogada = false;
	njogadas++;
	ultimasJogadas.push_back(jogada);
	
	pair<Estado,bool> jogadinha = campo.movePeca(jogada.first,jogada.second);
	campo = jogadinha.first;	

	vector<Jogada> possiveis = getJogadasPossiveis();

	//printJogadas(possiveis);

	if(!jogadinha.second || possiveis.size()==0) //se nao comeu peça ou nao tem mais jogadas possiveis
		passar();
	else
		if(jogadorAtual->tipo==HUMANO)
			esperandoJogada = true;
		else
			executarTurno();
}

void Jogo::executarTurno()
{
	jogadorAtual->setaEstadoAtual(campo);
	
	if(jogadorAtual->tipo==COMPUTADOR)
	{
		cout << "minimax!" << endl;
		executaJogada( jogadorAtual->retornaJogada(getJogadasPossiveis()) );
	}
	else
		esperandoJogada = true;
}

vector<Jogada> Jogo::tiraJogadasRepetidas( vector<Jogada> jogadas )
{
	for(int k=0; k<jogadas.size(); k++)
		for(int i=0; i<ultimasJogadas.size(); i++)
			if(jogadas[k].second == ultimasJogadas[i].first)
				jogadas.erase(jogadas.begin()+k);

	return jogadas;
}

vector<Jogada> Jogo::getJogadasPossiveis()
{
	vector<Jogada> jogadasPossiveis, jogadasObrigatorias;
	
	if( ultimasJogadas.size() )
		return getJogadasObrigatorias();
	else {
		jogadasObrigatorias = getJogadasObrigatorias();		
	
		if(jogadasObrigatorias.size())
			jogadasPossiveis = jogadasObrigatorias;
		else
			jogadasPossiveis = campo.listaPossibilidades( jogadorAtual->meuTime );
	}
	
	return jogadasPossiveis;	
}

vector<Jogada> Jogo::getJogadasObrigatorias()
{
	if(ultimasJogadas.size()) // já comeu uma peça neste turno
	{
		Jogada ultima = ultimasJogadas[ultimasJogadas.size()-1];
		//cout<<"obrigatorias jah comi: "<<campo.jogadasObrigatorias( ultima.second ).size()<<endl;
		return tiraJogadasRepetidas( campo.jogadasObrigatorias( ultima.second ) );
	}
	else // primeira jogada do turno
	{
		//cout<<"obrigatorias nao comi"<<endl;
		return campo.jogadasObrigatorias( jogadorAtual->meuTime );
	}
}

void Jogo::passar()
{
	// passa o turno
	if(jogadorAtual==jogador[0])
		jogadorAtual = jogador[1];
	else
		jogadorAtual = jogador[0];
		
	ultimasJogadas.clear();
	
	executarTurno();
}
