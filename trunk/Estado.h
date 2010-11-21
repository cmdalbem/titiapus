#pragma once

#include <vector>
using namespace std;

#include "constantes.h"
#include "utils.h"


class Estado
{
		public:
				Estado();
				Estado(const Estado & _estado);
				~Estado();

				casa 				pecas[NLIN][NCOL];
				int  				npecas[TOTAL_COR];


				vector<Ponto> 		listaPossibilidades( Ponto pto ) const;
				vector< Jogada > 	listaPossibilidades( cor cor_pecas ) const;
				vector<Estado> 		listaSucessores( Ponto pto) const;
				vector<Estado>  	listaSucessores( cor cor_pecas ) const;
				pair<Estado,bool> 	movePeca( Ponto origem, Ponto destino ) const;
				vector< Jogada > 	jogadasObrigatorias( cor cor_pecas ) const;
				vector< Jogada >	jogadasObrigatorias( Ponto peca ) const;
				void                print() const;
};
