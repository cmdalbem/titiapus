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
				Jogador*			jogadorAtual;
				int					niveisMinimax;
                
                // funções
                void				comecar();
                void				novo( tipoJogador jogadorBrancas, tipoJogador jogadorPretas );
                void				executaJogada( Jogada jogada );
                void				executarTurno();
                void				passar();
                vector<Jogada> 		getJogadasPossiveis();
        
        private:
                int 				njogadas;
                
                void				posicoesIniciais();
};

