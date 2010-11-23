#include "Jogador.h"

Jogador::Jogador(cor time, tipoJogador novoTipo, Estado &estadoAtual) : meuTime(time), tipo(novoTipo), estadoJogo(estadoAtual){}
Jogador::~Jogador() {}

void Jogador::setaEstadoAtual(Estado &estadoAtual)
{
	estadoJogo = estadoAtual;
}
