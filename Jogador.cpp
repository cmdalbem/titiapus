#include "Jogador.h"

Jogador::Jogador() {}
Jogador::Jogador(const Estado& estado, cor time) : estadoJogo(estado), meuTime(time) {}
Jogador::~Jogador() {}

void Jogador::setaEstadoAtual(const Estado& estadoAtual)
{
	estadoJogo = estadoAtual;
}
