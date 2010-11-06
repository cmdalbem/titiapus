#pragma once

#include <vector>
using namespace std;

#include "constantes.h"


float distanciaPontos( point a, point b );

bool estaContido( point pto, vector<point> ptos );

bool estaDentroCampo(int i, int j);
