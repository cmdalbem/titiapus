#include "Jogador.h"

Jogador::Jogador(cor time, tipoJogador novoTipo) : meuTime(time), tipo(novoTipo) {}
Jogador::~Jogador() {}

void Jogador::setaEstadoAtual(const Estado& estadoAtual)
{
	estadoJogo = estadoAtual;
}
