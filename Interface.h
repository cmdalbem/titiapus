#pragma once


#include <gtk/gtk.h>

#include "Jogo.h"


class Interface
{
		public:
				Interface();
				~Interface();
				
				Jogo 				*jogo;
				
				// gtk widgets
				GtkWidget 			*janela, *janelaConfig;
				GtkWidget 			*tela;
				GtkWidget			*dialog;
				GdkPixmap 			*pixmap; //mapa de pixels da tela do tabuleiro
				GtkWidget			*pretas_humano, *brancas_humano;
				GtkWidget			*painel1, *painel2, *painel3, *painel4;
				GtkWidget			*painelTurnos;
								
				bool				visPosicoes;
				
				void 			inicializa();
				
				// callbacks mouse
				void			mouseSobre( int x, int y );
				void			cliqueEsquerdo( int x, int y );
				void			cliqueDireito( int x, int y );
				pair<int,Ponto>	qualElemento( int x, int y );
				
				// callbacks botões
				void			comecar();
				void 			novo();
				void 			resetar();
				void			passar();
				void 			novo_ok();
				void 			novo_cancelar();
				void			mudaVisPosicoes();
				
		private:				
				// funções gerais
				void			atualiza();
				void			atualizaTela();
				void			atualizaPainel();
						
				// desenho
				void 			desenhaPecas();
				void 			desenhaPeca( int posx, int posy, cor acor );
				void 			marcaPosicao( int posx, int posy );
				void 			marcaSelecionada( Ponto peca );
				void 			marcaObrigatoria( Ponto peca );
				void 			desenhaTabuleiro();
				void			mostraPossibilidades( Ponto pto );
	
	
};
