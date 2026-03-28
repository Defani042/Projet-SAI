#ifndef _CARTE_H_
#define _CARTE_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "noyau/joueur.h"
#include "noyau/objet.h"
#include "noyau/ennemi.h"


typedef struct s_carte
{
    objet liste_objets;
    joueur j;
    ennemi liste_ennemi;
    
}s_carte;

typedef s_carte * carte;


carte creer_carte(objet liste_objets, joueur j);

void liberer_carte(carte c);

carte creer_carte_vide();

int game_over(carte c);

int objet_visible(joueur j, objet o);

#endif /*_CARTE_H_*/