#ifndef _DEPLACEMENT_H_
#define _DEPLACEMENT_H_

#include <stdlib.h>
#include <stdio.h>

#include "noyau/carte.h"
#include "noyau/collision.h"
#include "noyau/grille_global.h"
#include "noyau/aleatoire.h"

extern int nbkill;

void deplacer_joueur(carte c, double dirx, double diry, double dirz);

void deplacer_ennemi_vers_joueur(carte c, ennemi e, joueur joueur);

int essayer_deplacement(ennemi e, double dx, double dy, double dz);

void deplacer_ennemi_vers_joueur2(carte c, ennemi e, joueur j);

void avencer_vague_ennemi(carte c);

#endif /* _COLLISION_H_*/