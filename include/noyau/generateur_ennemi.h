#ifndef _GENERATEUR_ENNEMI_H_
#define _GENERATEUR_ENNEMI_H_

#include <stdio.h>
#include <stdlib.h>



#include "noyau/ennemi.h"
#include "noyau/carte_globale.h"
#include "noyau/aleatoire.h"

#define NB_TYPE_E 3
#define TANK 0
#define SOLDAT 1
#define ASSASIN 2


extern ennemi globale_ennemi_tab[NB_TYPE_E];

void init_tab_ennemi();



#endif /*_GENERATEUR_ENNEMI_H_*/