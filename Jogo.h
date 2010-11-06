#pragma once

#include "constantes.h"
#include "Estado.h"

class Jogo{

        private:
        
				//say no for private members!
        
        
        public:
                Jogo( tipoJogador jogadorBrancas, tipoJogador jogadorPretas );        
                ~Jogo();
                
                // funções
                void				novo( tipoJogador jogadorBrancas, tipoJogador jogadorPretas );
                void				executaJogada(  point origem, point destino );
                void				passar();
                void				testaJogadasObrigatorias();
                void				testaJogadasObrigatorias( point peca );
                
                // atributos
                vector< pair<point,point> > jogadasObrigatorias;
                Estado 						campo;
                int 						njogadas;
                tipoJogador					jogador[TOTAL_COR];
				cor							turnoJogador;
				int							niveisMinimax;
};

