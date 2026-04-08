#ifndef _GENERATEUR_CARTE_H_
#define _GENERATEUR_CARTE_H_

#include <stdio.h>
#include <stdlib.h>

#include "noyau/carte.h"

extern objet ciel1,ciel2,ciel3,ciel4,ciel5,ciel6;

carte creer_carte_test();

objet creer_rocher_aleatoire(objet sol);

objet creer_arbre_aleatoire(objet sol);

objet creer_maison_aleatoire(objet sol);

void creer_sol_aleatoire(carte c);

void creer_monde(carte c);

carte creer_carte_jeu();

#endif /*_GENERATEUR_CARTE_H_*/