#include <iostream>
using namespace std;
#include <math.h>

#include "Interface.h"
#include "utils.h"
#include <string.h>


Interface::Interface() {
	
	janela = NULL;
	tela = NULL;
	pixmap = NULL;
	visPosicoes = true;
}

Interface::~Interface() {}


void Interface::desenhaPecas()
{
	for(int i=0; i<NLIN; i++)
		for(int j=0; j<NCOL; j++)
			if( jogo->campo.pecas[i][j] != NADA)
				desenhaPeca( POS(i,j), jogo->campo.pecas[i][j]==PCBRANCA ? BRANCO : PRETO );	

	gtk_widget_draw(tela, NULL);
}

void Interface::desenhaPeca( int posx, int posy, cor acor )
{
	cairo_t *cr = gdk_cairo_create( pixmap );
	cairo_set_line_width( cr, 2.5);
	
	if (acor==BRANCO) {
		cairo_set_source_rgb( cr, 1, 1, 1);
		cairo_arc( cr, posx, posy, PECA_RAIO, 0, 2*M_PI);
		cairo_fill(cr);
		cairo_set_source_rgb( cr, 0, 0, 0);				   
		cairo_arc( cr, posx, posy , PECA_RAIO, 0, 2*M_PI);
		cairo_stroke(cr);
	}
	else {
		cairo_set_source_rgb( cr, 0, 0, 0);
		cairo_arc(cr, posx, posy, PECA_RAIO, 0, 2*M_PI);
		cairo_fill(cr);				   
	}
}


void Interface::desenhaTabuleiro()
{
	cairo_t *cr = gdk_cairo_create( pixmap );
	
	cairo_set_source_rgb( cr, 0, 0, 0);
	cairo_set_line_width( cr, 1.5);

	// linhas
	for(int i=0; i<NLIN; i++) {
		cairo_move_to( cr, FRAMEX, ((TELAY-2*FRAMEY)/((float)NLIN-1))*i + FRAMEY );
		cairo_line_to( cr, TELAX-FRAMEX, ((TELAY-2*FRAMEY)/((float)NLIN-1))*i + FRAMEY );
	}

	// colunas
	for(int i=0; i<NCOL; i++) {
		cairo_move_to( cr, ((TELAX-2*FRAMEX)/((float)NCOL-1))*i + FRAMEY, FRAMEY );
		cairo_line_to( cr, ((TELAX-2*FRAMEX)/((float)NCOL-1))*i + FRAMEY, TELAY-FRAMEY );
	}

	// diagonais
	int oscilador=1;
	for(int i=0; i<NLIN-1; i++) {
		for(int j=0; j<NCOL-1; j++) {
			cairo_move_to( cr, POS((i+oscilador),(j)) );
			cairo_line_to( cr, POS((i+!oscilador),(j+1)) );
			oscilador = !oscilador;
		}
		oscilador = !oscilador;
	}
	
	// números
	if(visPosicoes) {
		cairo_set_line_width( cr, 1);

		cairo_text_extents_t te;
		cairo_select_font_face (cr, "Georgia", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
		cairo_set_font_size (cr, 9);	
		
		char ch[3];
		for(int i=0; i<NLIN; i++) {
			for(int j=0; j<NCOL; j++) {
				sprintf(ch, "%i,%i", j+1,i+1);
				cairo_text_extents (cr, ch, &te);
				cairo_move_to (cr,  LIN(j) + 10 - j*7 - te.width / 2 - te.x_bearing, COL(i) - 5*(NLIN-i+1) - te.height / 2 - te.y_bearing);
				cairo_show_text (cr, ch);
			}
		}
	}
	
	
	cairo_stroke( cr );
}

void Interface::atualiza()
{
	atualizaTela();
	atualizaPainel();
}

void Interface::atualizaTela()
{
	// fundo branco
	gdk_draw_rectangle (pixmap,
					  janela->style->white_gc,
					  TRUE,
					  0, 0,
					  janela->allocation.width,
					  janela->allocation.height);
	desenhaTabuleiro();
	desenhaPecas();
	
	if(jogo->esperandoJogada)
		switch( ((JogadorHumano*)jogo->jogadorAtual)->estado )
		{
			case PARADO:
			{
				vector<Jogada> obrigatorias = jogo->getJogadasObrigatorias();
				for(int i=0; i<obrigatorias.size(); i++)
					marcaObrigatoria( obrigatorias[i].first );
				
				break;
			}
			
			case SELECIONADO:
				marcaSelecionada( ((JogadorHumano*)jogo->jogadorAtual)->pecaSelecionada );
				mostraPossibilidades( ((JogadorHumano*)jogo->jogadorAtual)->pecaSelecionada );		
				break;
		}
	
	gtk_widget_draw(tela, NULL);
}

void Interface::inicializa()
{
	if (pixmap)
		gdk_pixmap_unref(pixmap);

	pixmap = gdk_pixmap_new(janela->window,
						  janela->allocation.width,
						  janela->allocation.height,
						  -1);
						  
	atualiza();
}

void Interface::comecar()
{
	jogo->comecar();
	atualizaTela();
}

void Interface::novo()
{
	// janela de seleção de jogadores
	gtk_widget_show_all( dialog );
}

void Interface::resetar()
{
	jogo->novo( jogo->jogador[BRANCO]->tipo, jogo->jogador[PRETO]->tipo );
	
	atualiza();
}

void Interface::passar()
{
	jogo->passar();
	
	atualiza();
}

void Interface::novo_ok()
{
	gtk_widget_hide_all( dialog );
	
	tipoJogador jogadorBrancas = gtk_toggle_button_get_active( (GtkToggleButton*)brancas_humano )==TRUE ? HUMANO : COMPUTADOR;
	tipoJogador jogadorPretas = gtk_toggle_button_get_active( (GtkToggleButton*)pretas_humano )==TRUE ? HUMANO : COMPUTADOR;
	
	jogo->novo(jogadorBrancas,jogadorPretas );
	
	atualiza();
}

void Interface::novo_cancelar()
{
	gtk_widget_hide_all( dialog );
}

void Interface::mudaVisPosicoes()
{
	visPosicoes = !visPosicoes;
	atualizaTela();
}

void Interface::atualizaPainel()
{
	char txt[30];
	
	if(jogo->jogadorAtual->meuTime == PRETO)	
		sprintf(txt, "<big><b>[%s]</b></big>", jogo->jogador[PRETO]->tipo==COMPUTADOR ? "Máquina":"Humano");
	else
		sprintf(txt, "<big>%s</big>", jogo->jogador[PRETO]->tipo==COMPUTADOR ? "Máquina":"Humano");
	gtk_label_set_markup( (GtkLabel*)painel1, txt);
	sprintf(txt, "<big>%i</big>", jogo->campo.npecas[PRETO]);
	gtk_label_set_markup( (GtkLabel*)painel3, txt);
	
	if(jogo->jogadorAtual->meuTime == BRANCO)	
		sprintf(txt, "<big><b>[%s]</b></big>", jogo->jogador[BRANCO]->tipo==COMPUTADOR ? "Máquina":"Humano");
	else
		sprintf(txt, "<big>%s</big>", jogo->jogador[BRANCO]->tipo==COMPUTADOR ? "Máquina":"Humano");
	gtk_label_set_markup( (GtkLabel*)painel2, txt);
	sprintf(txt, "<big>%i</big>", jogo->campo.npecas[BRANCO]);
	gtk_label_set_markup( (GtkLabel*)painel4, txt);
	
	sprintf(txt, "%i", jogo->njogadas);
	gtk_label_set_markup( (GtkLabel*)painelTurnos, txt);

}

void Interface::mouseSobre( int x, int y )
{
	if( jogo->esperandoJogada &&
		((JogadorHumano*)jogo->jogadorAtual)->estado == PARADO )
	{		
		pair<int,Ponto> elem = qualElemento(x,y);

		cout<<elem.first<<endl;
		if(elem.first==PCPRETA || elem.first==PCBRANCA)
			mostraPossibilidades( elem.second );
		else
			atualizaTela();
	}
}


void Interface::cliqueEsquerdo( int x, int y )
{
	if(jogo->esperandoJogada) // estamos esperando uma entrada
	{
		pair<int,Ponto> clickd = qualElemento(x,y);
		
		if( clickd.first != -1 ) //clicou em uma casa				
			switch( ((JogadorHumano*)jogo->jogadorAtual)->cliqueEsquerdo( (casa)clickd.first, clickd.second ) )
			{
				case PARADO:
					puts("estado atual: parado");
					break;
				case SELECIONADO:
					puts("estado atual: selecionado");
					break;
				case DECIDIU:
					puts("estado atual: decidiu");
					jogo->executarTurno();
					break;
			}
	}
	
	atualiza();
}

pair<int,Ponto> Interface::qualElemento( int x, int y )
{
	int achou = -1;
	Ponto pto(-1,-1);
	
	for( int i=0; i<NLIN && achou==-1; i++ )
		
		for( int j=0; j<NCOL && achou==-1; j++ )
		
			if( distanciaPontos( Ponto(POS(i,j)), Ponto(x,y) ) < PECA_RAIO ) {
				achou = jogo->campo.pecas[i][j];
				pto = Ponto(i,j);
			}

	return pair<int,Ponto>(achou,pto);
}

void Interface::cliqueDireito( int x, int y )
{
	if(jogo->esperandoJogada) {
		((JogadorHumano*)jogo->jogadorAtual)->cliqueDireito( Ponto(x,y) );
		atualizaTela();
	}
}

void Interface::mostraPossibilidades( Ponto peca )
{		
	vector<Jogada> jogadasPossiveis = jogo->campo.getJogadasPossiveis( peca );	
	for(unsigned int i=0; i<jogadasPossiveis.size(); i++)
			marcaPosicao( POS(jogadasPossiveis[i].second.first,jogadasPossiveis[i].second.second) );
}


void Interface::marcaPosicao( int x, int y )
{
	cairo_t *cr = gdk_cairo_create( pixmap );
	
	cairo_set_source_rgb( cr, 1, 0, 0);
	cairo_arc( cr, x, y , PECA_RAIO/3., 0, 2*M_PI);
	cairo_stroke(cr);	
	
	gtk_widget_draw(tela, NULL);
}

void Interface::marcaSelecionada( Ponto peca )
{
	cairo_t *cr = gdk_cairo_create( pixmap );
	
	cairo_set_line_width( cr, 3);
	cairo_set_source_rgb( cr, 0, 0, 1);
	cairo_arc( cr, POS(peca.first,peca.second) , PECA_RAIO*1, 0, 2*M_PI);
	cairo_stroke(cr);	
	
	gtk_widget_draw(tela, NULL);
}	

void Interface::marcaObrigatoria( Ponto peca )
{
	cairo_t *cr = gdk_cairo_create( pixmap );
	
	cairo_set_line_width( cr, 3);
	double dashes[] = {5.0, 5.0};
	int    ndash  = sizeof (dashes)/sizeof(dashes[0]);
	double offset = -50.0;
	cairo_set_dash (cr, dashes, ndash, offset);
	
	cairo_set_source_rgb( cr, 1, 0, 0);
	cairo_arc( cr, POS(peca.first,peca.second) , PECA_RAIO*1.1, 0, 2*M_PI);
	cairo_stroke(cr);	
	
	gtk_widget_draw(tela, NULL);
}	
