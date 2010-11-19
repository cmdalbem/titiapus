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
    
    njogadas = 0;

    if(_jogadorBrancas == COMPUTADOR)
		jogador[BRANCO] = new JogadorComputador(BRANCO);
	else
		jogador[BRANCO] = new JogadorHumano(BRANCO);
		
	if(_jogadorPretas == COMPUTADOR)
		jogador[PRETO] = new JogadorComputador(PRETO);
	else
		jogador[PRETO] = new JogadorHumano(PRETO);
		
	jogadorAtual = jogador[PRETO];
    
	campo.npecas[BRANCO] = campo.npecas[PRETO] = 17;
}

void Jogo::executaJogada( Jogada jogada )
{
	njogadas++;
	
	pair<Estado,bool> novo = campo.movePeca(jogada.first,jogada.second);
	campo = novo.first;	
	
	passar();
}

void Jogo::executarTurno()
{
	jogadorAtual->setaEstadoAtual(campo);
	
	if(jogadorAtual->tipo==COMPUTADOR)
		executaJogada( jogadorAtual->retornaJogada(getJogadasPossiveis()) );
}

vector<Jogada> Jogo::getJogadasPossiveis()
{
	vector<Jogada> jogadasPossiveis, jogadasObrigatorias;
	
	jogadasObrigatorias = campo.jogadasObrigatorias( jogadorAtual->meuTime );
	if(jogadasObrigatorias.size())
		jogadasPossiveis = jogadasObrigatorias;
	else
		jogadasPossiveis = campo.listaPossibilidades( jogadorAtual->meuTime );
	
	return jogadasPossiveis;	
}

void Jogo::passar()
{
	// passa o turno
	if(jogadorAtual==jogador[0])
		jogadorAtual = jogador[1];
	else
		jogadorAtual = jogador[0];
		
	executarTurno();
}
