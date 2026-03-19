#ifndef _JOUEUR_H_
#define _JOUEUR_H_

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT 1;
#define VIE 100;
#define ATK 10;
#define JET 50;

#include "noyau/position.h"

typedef struct s_joueur
{
    double vie; /*vie du joueur*/
    position pos; /*position du joueur dans l'espace*/
    double atk; /*attaque*/
    double reg; /*régenération*/
    double jetpack; /*jet pack*/
    int niv;
    int xp;
    double vit;
}s_joueur;

typedef s_joueur * joueur;

joueur creer_joueur(position pos);

void liberer_joueur(joueur j);

void deplacement(joueur j,double dirx,double diry,double dirz);

#endif /*_JOUEUR_H_*/