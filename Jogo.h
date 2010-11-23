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
                Jogador*			jogador[TOTAL_COR];
				Jogador*			jogadorAtual;
				int					niveisMinimax;
                int 				njogadas;		
                bool				esperandoJogada;		
                
                // funções
                void				comecar();
                void				novo( tipoJogador jogadorBrancas, tipoJogador jogadorPretas );
                void				executaJogada( Jogada jogada );
                void				executarTurno();
                void				passar();
                vector<Jogada>		getJogadasObrigatorias();
                vector<Jogada>		getJogadasPossiveis();
        
        private:
                void				posicoesIniciais();
};

