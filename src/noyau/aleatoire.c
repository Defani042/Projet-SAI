#ifndef _ALEATOIRE_C_
#define _ALEATOIRE_C_

#include "noyau/aleatoire.h"

/*
R: génération d'un nombre entre a et b compris
E: 2 double a et b pour un intervalle ->[a,b]
S: 1 double entre a et b
A: Adrien
*/
double alea_double(double a, double b) {
    return a + (b - a) * ((double)rand() / RAND_MAX);
}

/*
R: génération d'un nombre entre a et b compris
E: 2 entier a et b pour un intervalle ->[a,b]
S: 1 entier entre a et b
A: Adrien
*/
int alea_int(int a, int b)
{
	return a + rand() % (b - a + 1);
}

#endif /*_ALEATOIRE_C_*/