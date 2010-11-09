#pragma once

#include "Estado.h"
#include "constantes.h"

typedef pair<point,point> Jogada; //Talvez isso nao devesse ficar aqui...

class Jogador
{
	public:
		Jogador();
		Jogador(const Estado& estado, cor time);
		~Jogador();

		void 			recebeEstadoAtual(const Estado& estadoAtual);
		virtual Jogada 	retornaJogada() = 0;
	protected:
		Estado estadoJogo;
		cor meuTime;
};

class JogadorComputador : public Jogador
{
	public:
		JogadorComputador();
		JogadorComputador(const Estado& estado, cor time);
		~JogadorComputador();

		Jogada 	        retornaJogada();
	private:
		static float    minimax(const Estado& inicial, float alfa, float beta, int _profundidade, cor _meuTime);
		static float 	utilidade(Estado estado, cor cor_time);

		int maxProfundidade;
};

class JogadorHumano : public Jogador
{
	public:
		JogadorHumano();
		JogadorHumano(const Estado& estado, cor time);
		~JogadorHumano();

		Jogada retornaJogada();
	private:
};
