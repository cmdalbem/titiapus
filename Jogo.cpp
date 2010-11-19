#include <iostream>
using namespace std;

#include "constantes.h"

#include "Jogo.h"

#include "IA.h"



Jogo::Jogo( tipoJogador _jogadorBrancas, tipoJogador _jogadorPretas )
{
	turnoJogador = PRETO;
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

void Jogo::novo( tipoJogador _jogadorBrancas, tipoJogador _jogadorPretas )
{
    posicoesIniciais();
    
    njogadas = 0;

    _jogadorBrancas == MAQUINA ? jogador[BRANCO] = new JogadorComputador() : jogador[BRANCO] = new JogadorHumano();
    _jogadorPretas == MAQUINA ? jogador[PRETO] = new JogadorComputador() : jogador[PRETO] = new JogadorHumano();
    
	campo.npecas[BRANCO] = campo.npecas[PRETO] = 17;
}

void Jogo::executaJogada( Jogada jogada )
{
	njogadas++;
	
	pair<Estado,bool> novo = campo.movePeca(jogada.first,jogada.second);
	campo = novo.first;
	
}

void Jogo::executarTurno()
{
	vector<Jogada> jogadasPossiveis;
	
	
	
	 
	testaJogadasObrigatorias();
	
	jogador[turnoJogador].setaEstadoAtual(campo);
	
	executaJogada( jogador[turnoJogador].retornaJogada() );

	// passa o turno
	turnoJogador = turnoJogador==BRANCO ? PRETO : BRANCO;
}

void Jogo::testaJogadasObrigatorias()
{
	jogadasObrigatorias.clear();
	
	jogadasObrigatorias = campo.jogadasObrigatorias( turnoJogador );
	
	cout<<jogadasObrigatorias.size()<<" jogadas obrigatorias"<<endl;
}

void Jogo::testaJogadasObrigatorias( point peca )
{
	jogadasObrigatorias.clear();
	
	jogadasObrigatorias = campo.jogadasObrigatorias( peca );
	
	cout<<jogadasObrigatorias.size()<<" jogadas obrigatorias"<<endl;
}
