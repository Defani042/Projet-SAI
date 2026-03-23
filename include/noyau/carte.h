#ifndef _CARTE_H_
#define _CARTE_H_

#include <stdio.h>
#include <stdlib.h>


#include "noyau/joueur.h"
#include "noyau/objet.h"

typedef struct s_carte
{
    objet liste_objets;
    joueur j;
}s_carte;

typedef s_carte * carte;


carte creer_carte(objet liste_objets, joueur j);

void liberer_carte(carte c);

carte creer_carte_vide();


int collision_hitbox(
    double x1, double y1, double z1,
    double w1, double h1, double l1,
    double x2, double y2, double z2,
    double w2, double h2, double l2
);

objet detecter_collision_joueur(carte c);

void deplacer_joueur(carte c, double dirx, double diry, double dirz);

int game_over(carte c);

int objet_visible(joueur j, objet o);

#endif /*_CARTE_H_*/