#ifndef _GRILLE_GLOBAL_H_
#define _GRILLE_GLOBAL_H_

#include "grille.h"

/* Grille statique : murs, arbres, décor */
extern grille grille_statique;

/* Grille dynamique : ennemis et objets mobiles */
extern grille grille_dynamique;


void maj_grille_dynamique(ennemi liste_ennemis);

#endif /* _GRILLE_GLOBAL_H_ */