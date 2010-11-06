#include <iostream>
using namespace std;

#include "constantes.h"

#include "Jogo.h"

#include "IA.h"



Jogo::Jogo( tipoJogador _jogadorBrancas, tipoJogador _jogadorPretas )
{
	turnoJogador = PRETO;
	novo( _jogadorBrancas, _jogadorPretas );
	
	passar();
}

Jogo::~Jogo() {}


void Jogo::novo( tipoJogador _jogadorBrancas, tipoJogador _jogadorPretas )
{
    njogadas = 0;

    jogador[BRANCO] = _jogadorBrancas;
    jogador[PRETO] = _jogadorPretas;    
    
    // posições inicias das peças
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

	campo.npecas[BRANCO] = campo.npecas[PRETO] = 17;
	
	testaJogadasObrigatorias();
}

void Jogo::executaJogada(  point origem, point destino )
{
	njogadas++;
	
	pair<Estado,bool> novo = campo.movePeca(origem,destino);
	campo = novo.first;
	
	vector< pair<point,point> > quaisPodeComer = campo.jogadasObrigatorias(destino);
	
	if(quaisPodeComer.size()==0 || jogador[turnoJogador]==MAQUINA)
		passar();
	else
		testaJogadasObrigatorias();
}

void Jogo::passar()
{
	turnoJogador = turnoJogador==BRANCO ? PRETO : BRANCO;	
	cout<<"-------- Vez do jogador "<< (turnoJogador==BRANCO?"BRANCO":"PRETO") << endl;
	
	if(jogador[turnoJogador]==MAQUINA)
	{
		jogadasObrigatorias.clear();
	
		jogadasObrigatorias = campo.jogadasObrigatorias( turnoJogador );
		
		IA ia(niveisMinimax,campo,turnoJogador,jogadasObrigatorias);
		pair<point,point> decisao = ia.decideJogada();
		cout<<"$ Michael jogou: "<<decisao.first.first+1<<","<<decisao.first.second+1<<" -> "<<decisao.second.first+1<<","<<decisao.second.second+1<<endl;
		executaJogada(  decisao.first, decisao.second );
	}
	else{	
		testaJogadasObrigatorias();
	}
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
