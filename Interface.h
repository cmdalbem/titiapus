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
				GtkWidget 			*janela;
				GtkWidget 			*tela;
				GtkWidget			*dialog;
				GdkPixmap 			*pixmap; //mapa de pixels da tela do tabuleiro
				GtkWidget			*pretas_humano, *brancas_humano;
				GtkWidget			*painel1, *painel2, *painel3, *painel4;
								
				
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
				
		private:				
				// funções gerais
				void 			selecionaPeca( Ponto peca );
				void			atualiza();
				void			atualizaTela();
				void			atualizaPainel();
						
				// desenho
				void 			desenhaPecas();
				void 			desenhaPeca( int posx, int posy, cor acor );
				void 			desenhaMarcador( int posx, int posy );
				void 			desenhaTabuleiro();
				void			mostraPossibilidades( Ponto pto );
	
	
};
