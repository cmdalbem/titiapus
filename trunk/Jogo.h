#pragma once

#include "constantes.h"
#include "Estado.h"
#include "JogadorComputador.h"
#include "JogadorHumano.h"


class Jogo{

        public:
                Jogo( tipoJogador jogadorBrancas, tipoJogador jogadorPretas );        
                ~Jogo();
                
                // atributos
                Estado 				campo;
				//vector<Jogada> 		jogadasObrigatorias;
                Jogador*			jogador[TOTAL_COR];
				cor					turnoJogador;
				int					niveisMinimax;
                
                // funções
                void				novo( tipoJogador jogadorBrancas, tipoJogador jogadorPretas );
                void				executaJogada( Jogada jogada );
                void				executarTurno();
                void				testaJogadasObrigatorias();
                void				testaJogadasObrigatorias( Ponto peca );
        
        private:
                int 				njogadas;
                
                void				posicoesIniciais();
};

