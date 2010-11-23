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
            campo.setaCasa(i,j,PCPRETA);
    
    for(int i=3; i<5; i++)
        for(int j=0; j<NCOL; j++)
            campo.setaCasa(i,j,PCBRANCA);
            
    campo.setaCasa(2,0,PCBRANCA);
    campo.setaCasa(2,1,PCPRETA);
    campo.setaCasa(2,2,PCBRANCA);
    campo.setaCasa(2,3,NADA);
    campo.setaCasa(2,4,PCPRETA);
    campo.setaCasa(2,5,PCBRANCA);
    campo.setaCasa(2,6,PCPRETA);
}

void Jogo::comecar()
{
	executarTurno();
}

void Jogo::novo( tipoJogador _jogadorBrancas, tipoJogador _jogadorPretas )
{
    posicoesIniciais();
    
    campo.ultimasJogadas.clear();
    njogadas = 0;
    esperandoJogada = false;

    if(_jogadorBrancas == COMPUTADOR)
		jogador[BRANCO] = new JogadorComputador(BRANCO,campo,niveisMinimax);
	else
		jogador[BRANCO] = new JogadorHumano(BRANCO,campo);
		
	if(_jogadorPretas == COMPUTADOR)
		jogador[PRETO] = new JogadorComputador(PRETO,campo,niveisMinimax);
	else
		jogador[PRETO] = new JogadorHumano(PRETO,campo);
		
	jogadorAtual = jogador[BRANCO];
    
	campo.npecas[BRANCO] = campo.npecas[PRETO] = 17;
}

void Jogo::executaJogada( Jogada jogada )
{
	/*//cout<<"EXECUTOU MOVIMENTO"<<endl;
	esperandoJogada = false;
	njogadas++;	
	
	//pair<Estado,bool> jogadinha = campo.movePeca(jogada.first,jogada.second);
	//campo = jogadinha.first;
	
	//vector<Jogada> possiveis = campo.getJogadasPossiveis(jogadorAtual->meuTime);

	//printJogadas(possiveis);

	if(!jogadinha.second || possiveis.size()==0) //se nao comeu peça ou nao tem mais jogadas possiveis
		passar();
	else
	{
		if(jogadorAtual->tipo==HUMANO)
			esperandoJogada = true;
		else
			executarTurno();
	}*/
}

void Jogo::executarTurno()
{
	jogadorAtual->setaEstadoAtual(campo);
	
	if(jogadorAtual->tipo==HUMANO)
	{
		esperandoJogada = true;
		
		if( ((JogadorHumano*)jogadorAtual)->estado == DECIDIU )
		{
			((JogadorHumano*)jogadorAtual)->estado = PARADO;
			
			Estado anterior = campo;
			campo = jogadorAtual->retornaJogada();
			
			bool comeu = (anterior.npecas[BRANCO]+anterior.npecas[PRETO]) -
						 (campo.npecas[BRANCO]+campo.npecas[PRETO])
						 > 0;
			
			esperandoJogada = false;
			
			vector<Jogada> possiveis = campo.getJogadasPossiveis(jogadorAtual->meuTime);
			
			if(!comeu || possiveis.size()==0) //se nao comeu peça ou nao tem mais jogadas possiveis
				passar();
			else
				esperandoJogada = true;			
		}
	}
	if(jogadorAtual->tipo==COMPUTADOR)
		{
			campo = jogadorAtual->retornaJogada();
			passar();
		}
}

void Jogo::passar()
{
	// passa o turno
	if( jogadorAtual==jogador[0] ) {
		cout << "Jogador 0:" << endl;
		jogadorAtual = jogador[1];
	}
	else {
		cout << "Jogador 1:" << endl;
		jogadorAtual = jogador[0];
	}
	//printJogadas(campo.ultimasJogadas);
		
	campo.ultimasJogadas.clear();
	
	executarTurno();
}

vector<Jogada> Jogo::getJogadasObrigatorias()
{
	return campo.getJogadasObrigatorias( jogadorAtual->meuTime );	
}

vector<Jogada> Jogo::getJogadasPossiveis()
{
	return campo.getJogadasPossiveis( jogadorAtual->meuTime );
}
