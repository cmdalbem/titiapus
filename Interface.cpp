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
	
	if (acor==BRANCO)
	{
		cairo_set_source_rgb( cr, 1, 1, 1);
		cairo_arc( cr, posx, posy, PECA_RAIO, 0, 2*M_PI);
		cairo_fill(cr);
		cairo_set_source_rgb( cr, 0, 0, 0);				   
		cairo_arc( cr, posx, posy , PECA_RAIO, 0, 2*M_PI);
		cairo_stroke(cr);
	}
	else
	{
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


	// desenhando as linhas
	for(int i=0; i<NLIN; i++) {
		cairo_move_to( cr, FRAMEX, ((TELAY-2*FRAMEY)/((float)NLIN-1))*i + FRAMEY );
		cairo_line_to( cr, TELAX-FRAMEX, ((TELAY-2*FRAMEY)/((float)NLIN-1))*i + FRAMEY );
	}

	// desenhando as colunas
	for(int i=0; i<NCOL; i++) {
		cairo_move_to( cr, ((TELAX-2*FRAMEX)/((float)NCOL-1))*i + FRAMEY, FRAMEY );
		cairo_line_to( cr, ((TELAX-2*FRAMEX)/((float)NCOL-1))*i + FRAMEY, TELAY-FRAMEY );
	}

	// desenhando as diagonais
	int oscilador=1;
	for(int i=0; i<NLIN-1; i++) {
		for(int j=0; j<NCOL-1; j++) {
			cairo_move_to( cr, POS((i+oscilador),(j)) );
			cairo_line_to( cr, POS((i+!oscilador),(j+1)) );
			oscilador = !oscilador;
		}
		oscilador = !oscilador;
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

void Interface::novo()
{
	acaoPendente = SELECAO;
	gtk_widget_show_all( dialog );
}

void Interface::resetar()
{
	jogo->novo( jogo->jogador[BRANCO],jogo->jogador[PRETO] );
	
	atualiza();
}

void Interface::passar()
{
	jogo->jogadasObrigatorias.clear();
	acaoPendente = SELECAO;
	jogo->passar();
}

void Interface::novo_ok()
{
	gtk_widget_hide_all( dialog );
	
	tipoJogador jogadorBrancas = gtk_toggle_button_get_active( (GtkToggleButton*)brancas_humano )==TRUE ? HUMANO : MAQUINA;
	tipoJogador jogadorPretas = gtk_toggle_button_get_active( (GtkToggleButton*)pretas_humano )==TRUE ? HUMANO : MAQUINA;
	
	jogo->novo(jogadorBrancas,jogadorPretas );
	
	atualiza();
}

void Interface::novo_cancelar()
{
	gtk_widget_hide_all( dialog );
}

void Interface::atualizaPainel()
{
	char txt[30];
	
	sprintf(txt, "<big><b>%s</b></big>", jogo->jogador[PRETO]==MAQUINA ? "Máquina":"Humano");
	gtk_label_set_markup( (GtkLabel*)painel1, txt);
	sprintf(txt, "<big>%i</big>", jogo->campo.npecas[PRETO]);
	gtk_label_set_markup( (GtkLabel*)painel3, txt);
	
	sprintf(txt, "<big><b>%s</b></big>", jogo->jogador[BRANCO]==MAQUINA ? "Máquina":"Humano");
	gtk_label_set_markup( (GtkLabel*)painel2, txt);
	sprintf(txt, "<big>%i</big>", jogo->campo.npecas[BRANCO]);
	gtk_label_set_markup( (GtkLabel*)painel4, txt);

}

pair<int,point> Interface::qualElemento( int x, int y )
{
	int achou = -1;
	point pto(-1,-1);
	
	for( int i=0; i<NLIN && achou==-1; i++ )
		
		for( int j=0; j<NCOL && achou==-1; j++ )
		
			if( distanciaPontos( point(POS(i,j)), point(x,y) ) < PECA_RAIO )
			{
				achou = jogo->campo.pecas[i][j];
				pto = point(i,j);
			}


	return pair<int,point>(achou,pto);
}


void Interface::mouseSobre( int x, int y )
{
	if(acaoPendente==SELECAO) {
		casa pecaRequerida;
		pair<int,point> elem = qualElemento(x,y);
			
		
		if(jogo->turnoJogador==BRANCO)
			pecaRequerida = PCBRANCA;
		else
			pecaRequerida = PCPRETA;

		if( elem.first == pecaRequerida )
			mostraPossibilidades( elem.second.first, elem.second.second );
		else
			atualizaTela();
	}
}


void Interface::cliqueEsquerdo( int x, int y )
{
	casa pecaRequerida;
	
	if( jogo->jogador[jogo->turnoJogador]==HUMANO ) //é a vez de um humano jogar
	{
		if(jogo->turnoJogador==BRANCO)
			pecaRequerida = PCBRANCA;
		else
			pecaRequerida = PCPRETA;
			

		pair<int,point> clickd = qualElemento(x,y); //descobrimos em qual elemento o usuario clicou
		
		if( acaoPendente==SELECAO && clickd.first==pecaRequerida ){ //selecionou uma peca válida
		
			selecionaPeca(clickd.second);
			acaoPendente = ACAO;
			mostraPossibilidades(pecaSelecionada.first,pecaSelecionada.second);
		}
		else if( acaoPendente==ACAO && clickd.second==pecaSelecionada ) //clicou denovo na mesma peça
		{
				deseleciona();
		}
		else if( acaoPendente==ACAO && clickd.first==NADA ) //tentou mover a peca para um espaço vazio
		{
			bool valido=false;
			
			if( jogo->jogadasObrigatorias.size()>0 )
			{
				for(unsigned int i=0; i<jogo->jogadasObrigatorias.size(); i++)
					if(   jogo->jogadasObrigatorias[i].first.first==pecaSelecionada.first && jogo->jogadasObrigatorias[i].first.second==pecaSelecionada.second
					   && jogo->jogadasObrigatorias[i].second.first==clickd.second.first && jogo->jogadasObrigatorias[i].second.second==clickd.second.second )
						valido=true;
			}
			else
			{
				vector<point> possibilidades = jogo->campo.listaPossibilidades(pecaSelecionada.first,pecaSelecionada.second);
				if( estaContido(clickd.second,possibilidades) ) //movimento válido
					valido=true;
			}
			
			if(valido)
			{
				jogo->executaJogada(pecaSelecionada,clickd.second);
				acaoPendente = SELECAO;
				atualiza();
			}
		}
		
	}
	else {} //é a vez de a máquina jogar, então a interface ignora o clique
}

void Interface::cliqueDireito( int x, int y )
{
	deseleciona();
	atualizaTela();
}

void Interface::deseleciona()
{
	atualizaTela();
	acaoPendente = SELECAO;	
}

void Interface::mostraPossibilidades( int x, int y )
{
	if( jogo->jogadasObrigatorias.size()>0 )
	{
		for(unsigned int i=0; i<jogo->jogadasObrigatorias.size(); i++)
			if( jogo->jogadasObrigatorias[i].first.first==x && jogo->jogadasObrigatorias[i].first.second==y )
				desenhaMarcador( POS(jogo->jogadasObrigatorias[i].second.first,jogo->jogadasObrigatorias[i].second.second) );
	}
	else
	{
		vector<point> possibilidades = jogo->campo.listaPossibilidades(x,y);
		
		if( possibilidades.size() )	
			for(unsigned int i=0; i<possibilidades.size(); i++)
				desenhaMarcador( POS(possibilidades[i].first,possibilidades[i].second) );
	}
}


void Interface::desenhaMarcador( int x, int y )
{
	cairo_t *cr = gdk_cairo_create( pixmap );
	
	
	
	cairo_set_source_rgb( cr, 0, 1, 0);
	cairo_arc( cr, x, y , PECA_RAIO/3., 0, 2*M_PI);
	cairo_stroke(cr);	
	
	gtk_widget_draw(tela, NULL);
}

void Interface::selecionaPeca( point peca )
{
	pecaSelecionada = peca;
	
	// desenho:
	
	cairo_t *cr = gdk_cairo_create( pixmap );
	
	double dashes[] = {5.0, 5.0};
	int    ndash  = sizeof (dashes)/sizeof(dashes[0]);
	double offset = -50.0;
	cairo_set_dash (cr, dashes, ndash, offset);

	cairo_set_source_rgb( cr, 0, 0, 1);
	cairo_arc( cr, POS(peca.first,peca.second) , PECA_RAIO*1.2, 0, 2*M_PI);
	cairo_stroke(cr);	
	
	gtk_widget_draw(tela, NULL);
}	
