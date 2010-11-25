#include <gtk/gtk.h>
#include <iostream>

using namespace std;

#include "constantes.h"
#include "Jogo.h"
#include "Interface.h"


// Globais
Interface interface;



void novo_ok(GtkWidget *widget, gpointer label) { interface.novo_ok(); }

void novo_cancelar(GtkWidget *widget, gpointer label) { interface.novo_cancelar(); }

void novo(GtkWidget *widget, gpointer label) { interface.novo(); }

void resetar(GtkWidget *widget, gpointer label) { interface.resetar(); }

void comecar(GtkWidget *widget, gpointer label) { interface.comecar(); }

void passar(GtkWidget *widget, gpointer label) { interface.passar(); }
    
void visPosicoes(GtkWidget *widget, gpointer label) { interface.mudaVisPosicoes(); }
    
    
void on_window_destroy (GtkObject *object, gpointer user_data)
// Fecha a GTK ao receber o sinal de que a janela principal foi fechada
{
        gtk_main_quit();
}

void niveisMinimaxCallback (GtkSpinButton *spinbutton, gpointer user_data)
// Atualiza variável com o valor do spinner referente aos Niveis de Minimax
{
	interface.jogo->niveisMinimax = gtk_spin_button_get_value_as_int(spinbutton);	
	//cout << "niveis minimax: " << interface.jogo->niveisMinimax << endl;
}

void clique (GtkWidget *widget, GdkEventButton *event, gpointer data)
// Trata sinais de clique na área do tabuleiro
{
  if( event->button == 1 )
	interface.cliqueEsquerdo(event->x,event->y);
  if( event->button == 3 )
	interface.cliqueDireito(event->x,event->y);
}

void movimento (GtkWidget *widget, GdkEventButton *event, gpointer data)
// Trata sinais de movimento de mouse na área do tabuleiro
{
	//interface.mouseSobre( event->x, event->y );
}

static gint configure_event (GtkWidget *widget, GdkEventConfigure *event)
// Inicialização padrão da tela
{
	interface.inicializa();
	return TRUE;
}

static gint expose_event (GtkWidget *widget, GdkEventExpose *event)
// Atualização da tela do tabuleiro
{
  gdk_draw_pixmap(widget->window,
                  widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                  interface.pixmap,
                  event->area.x, event->area.y,
                  event->area.x, event->area.y,
                  event->area.width, event->area.height);
	
  return FALSE;
}


int main (int argc, char *argv[])
{        
        interface.jogo = new Jogo( HUMANO, HUMANO );
        
        
        GtkBuilder *builder;
        
        // Inicializa GTK
        gtk_init (&argc, &argv);
        
        // lê XML da Glade
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "gui/gui2.glade", NULL);

        // recupera ponteiros de widgets do XML da Glade
        interface.janela = GTK_WIDGET (gtk_builder_get_object (builder, "janela"));
        interface.janelaConfig = GTK_WIDGET (gtk_builder_get_object (builder, "janelaConfig"));
			//gdk_gc_set_line_attributes(interface.janela->style->black_gc, 2, (GdkLineStyle)1,(GdkCapStyle)1,(GdkJoinStyle)1);
        interface.tela = GTK_WIDGET (gtk_builder_get_object (builder, "tela"));
			gtk_widget_set_size_request(interface.tela, TELAX, TELAY);
		interface.dialog = GTK_WIDGET (gtk_builder_get_object (builder, "dialog_novo"));
		interface.pretas_humano = GTK_WIDGET (gtk_builder_get_object (builder, "pretas_humano"));
		interface.brancas_humano = GTK_WIDGET (gtk_builder_get_object (builder, "brancas_humano"));
		interface.painel1 = GTK_WIDGET (gtk_builder_get_object (builder, "painel1"));
		interface.painel2 = GTK_WIDGET (gtk_builder_get_object (builder, "painel2"));
		interface.painel3 = GTK_WIDGET (gtk_builder_get_object (builder, "painel3"));
		interface.painel4 = GTK_WIDGET (gtk_builder_get_object (builder, "painel4"));
		interface.painelTurnos = GTK_WIDGET (gtk_builder_get_object (builder, "painelTurnos"));

		// conecta sinais das callbacks com a tela
		g_signal_connect(interface.janela, "destroy", G_CALLBACK(on_window_destroy), NULL);
		g_signal_connect(interface.tela, "configure_event", (GtkSignalFunc) configure_event, NULL);
		g_signal_connect(interface.tela, "expose_event", (GtkSignalFunc) expose_event, NULL);
		g_signal_connect(interface.tela, "button_press_event", (GtkSignalFunc) clique, NULL);
		g_signal_connect(interface.tela, "motion_notify_event", (GtkSignalFunc) movimento, NULL);
			gtk_widget_set_events (interface.tela, GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK); // habilita mensagem de captura de clique no tabuleiro

		
		// botão OK da dialog de Novo Jogo
		g_signal_connect( GTK_WIDGET (gtk_builder_get_object (builder, "novo_ok")),
						  "clicked", G_CALLBACK(novo_ok), NULL);
		// botão CANCELAR da dialog de Novo Jogo
		g_signal_connect( GTK_WIDGET (gtk_builder_get_object (builder, "novo_cancelar")),
						  "clicked", G_CALLBACK(novo_cancelar), NULL);						  
		// botão COMECAR
		g_signal_connect( GTK_WIDGET (gtk_builder_get_object (builder, "botaoComecar")),
						  "clicked", G_CALLBACK(comecar), NULL);
		// botão PASSAR
		g_signal_connect( GTK_WIDGET (gtk_builder_get_object (builder, "botaoPassar")),
						  "clicked", G_CALLBACK(passar), NULL);
		// spinner NIVEIS DE MINIMAX
		g_signal_connect( GTK_WIDGET (gtk_builder_get_object (builder, "niveisMinimax")),
						  "value-changed", G_CALLBACK(niveisMinimaxCallback), NULL);
		
		// opções do menu superior
		g_signal_connect( GTK_WIDGET (gtk_builder_get_object (builder, "menuComecar")),
						  "activate", G_CALLBACK(comecar), NULL);						  
		g_signal_connect( GTK_WIDGET (gtk_builder_get_object (builder, "menuResetar")),
						  "activate", G_CALLBACK(resetar), NULL);						  
		g_signal_connect( GTK_WIDGET (gtk_builder_get_object (builder, "menuNovo")),
						  "activate", G_CALLBACK(novo), NULL);			  						  
		g_signal_connect( GTK_WIDGET (gtk_builder_get_object (builder, "menuSair")),
						  "activate", G_CALLBACK(gtk_main_quit), NULL);
		g_signal_connect( GTK_WIDGET (gtk_builder_get_object (builder, "menuVis")),
						  "activate", G_CALLBACK(visPosicoes), NULL);
						  						  
						  

        gtk_widget_show (interface.janela);
        gtk_widget_show (interface.janelaConfig);
        
        // GTK Main loop
        gtk_main();
        
        return 0;
}
