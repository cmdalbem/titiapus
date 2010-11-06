#pragma once

#include "constantes.h"
#include "Estado.h"
#include "Jogo.h"

#include <map>
using namespace std;

class IA
{
		public:
			IA( int profundidade, Estado estado, cor meu_time );
			IA( int profundidade, Estado estado, cor meu_time, vector< pair<point,point> > jogadasObrigatorias );
			~IA() {};
		
			// atributos
			Jogo 						*jogo;
			int							profundidade;
			Estado						estado;
			vector< pair<point,point> > jogadasObrigatorias;
			cor							meu_time;
		
			// funções
			pair<point, point> 	decideJogada();
			static float 		minimax(Estado inicial, int _profundidade, float alfa, float beta, cor cor_time);
			static float 		utilidade(Estado estado, cor cor_time);
			
};
