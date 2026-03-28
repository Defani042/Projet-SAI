#ifndef _COLLISION_H_
#define _COLLISION_H_

#include <stdlib.h>
#include <stdio.h>


#include "noyau/carte.h"


int collision_hitbox(
    double x1, double y1, double z1,
    double w1, double h1, double l1,
    double x2, double y2, double z2,
    double w2, double h2, double l2
);

int collision_objet(
    double x1, double y1, double z1,
    double w1, double h1, double l1,
    double x2, double y2, double z2,
    double w2, double h2, double l2
);

objet detecter_collision_joueur(carte c);

objet detecter_collision_ennemi_objet(carte c,ennemi e);

objet detecter_collision_ennemi_ennemi(carte c,ennemi e);

#endif /* _COLLISION_H_ */