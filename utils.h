#pragma once

#include <vector>
using namespace std;

#include "constantes.h"


float distanciaPontos( Ponto a, Ponto b );

bool estaContido( Ponto pto, vector<Ponto> ptos );

bool estaDentroCampo(int i, int j);
