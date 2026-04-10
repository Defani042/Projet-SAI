#ifndef _GENERATEUR_ENNEMI_H_
#define _GENERATEUR_ENNEMI_H_

#include <stdio.h>
#include <stdlib.h>



#include "noyau/ennemi.h"
#include "noyau/carte_globale.h"
#include "noyau/aleatoire.h"
#include "noyau/collision.h"
#include "noyau/grille_global.h"
#include "noyau/difficulte.h"

#define NB_TYPE_E 4
#define TANK 0
#define SOLDAT 1
#define ASSASIN 2
#define SUPER_SPRINTER 3


extern ennemi globale_ennemi_tab[NB_TYPE_E];

void init_tab_ennemi();

ennemi creer_ennemi_alea(carte c);



#endif /*_GENERATEUR_ENNEMI_H_*/