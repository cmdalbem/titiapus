#include "utils.h"

#include "constantes.h"

#include "math.h"
#include "vector"
using namespace std;


float distanciaPontos( point a, point b )
{
	return sqrt( pow((a.first - b.first),2) + pow((a.second - b.second),2) );
}

bool estaContido( point pto, vector<point> ptos )
{
	for(unsigned int i=0; i<ptos.size(); i++)
		if(ptos[i]==pto)
			return true;
	return false;
}

bool estaDentroCampo(int i, int j)
{
	return ((i < NLIN) &&
	  (i >= 0) &&
	  (j < NCOL) &&
	  (j >= 0) );
}