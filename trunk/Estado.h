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
				
				vector<point> 				listaPossibilidades( int i, int j );
				vector< pair<point,point> > listaPossibilidades( cor cor_pecas );
				vector<Estado> 				listaSucessores( int i, int j );
				vector<Estado>  			listaSucessores( cor cor_pecas );
				pair<Estado,bool> 			movePeca( point origem, point destino );
				vector< pair<point,point> > jogadasObrigatorias( cor cor_pecas );
				vector< pair<point,point> >	jogadasObrigatorias( point peca );
};
