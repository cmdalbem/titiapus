#pragma once

#include <vector>
using namespace std;

#include "constantes.h"
#include "utils.h"

typedef unsigned short int u_int16;
class Linha
{
	public:
		Linha() {}
		Linha(const Linha& other) { set(other.get()); }
		Linha(const u_int16 lin) { set(lin); }
		~Linha() {}


        u_int16 get() const { return _linha; }

        void set (u_int16 lin) { _linha = lin; }
		void set(int index, casa valor);
		void limpaReservadas();

		casa operator[] (int index) const;
		Linha& operator= (const Linha& outro) { set(outro.get()); return *this; }
		//bool operator< (const Linha& outro) const { return this->get() < outro.get(); }

	private:
		u_int16 _linha;
};

//----------------------------------------------------------

class Estado
{
		public:
				Estado();
				Estado(const Estado & _estado);
				~Estado();

				Linha 				pecas[NLIN];
				int  				npecas[TOTAL_COR];

				void                setaCasa(int x, int y, casa valor);
				void                limpaReservadas();

				vector< Jogada >	listaPossibilidades( Ponto peca ) const;
				vector< Jogada > 	listaPossibilidades( cor cor_pecas ) const;
				vector<Estado> 		listaSucessores( Ponto pto) const;
				vector<Estado>  	listaSucessores( cor cor_pecas ) const;
				pair<Estado,bool> 	movePeca( Ponto origem, Ponto destino ) const;
				vector< Jogada > 	jogadasObrigatorias( cor cor_pecas ) const;
				vector< Jogada >	jogadasObrigatorias( Ponto peca ) const;
				void                print() const;
};
