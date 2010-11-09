#pragma once

#include <vector>
using namespace std;

#include "constantes.h"


class Estado
{
		public:
				Estado();
				Estado(const Estado & _estado);
				~Estado();

				casa 				pecas[NLIN][NCOL];
				int  				npecas[TOTAL_COR];

				vector<point> 				listaPossibilidades( int i, int j ) const;
				vector< pair<point,point> > listaPossibilidades( cor cor_pecas ) const;
				vector<Estado> 				listaSucessores( int i, int j ) const;
				vector<Estado>  			listaSucessores( cor cor_pecas ) const;
				pair<Estado,bool> 			movePeca( point origem, point destino ) const;
				vector< pair<point,point> > jogadasObrigatorias( cor cor_pecas ) const;
				vector< pair<point,point> >	jogadasObrigatorias( point peca ) const;
};
