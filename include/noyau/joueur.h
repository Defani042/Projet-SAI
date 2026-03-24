#ifndef _JOUEUR_H_
#define _JOUEUR_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "config/config.h"
#include "noyau/position.h"

#define DEFAULT 1
#define VIE 100
#define ATK 10
#define JET 50
#define SEUIL 100

typedef struct s_joueur
{
    double vie_max;
    double vie; /*vie du joueur*/
    position pos; /*position du joueur dans l'espace*/
    position dir; /*position ou regarde le joueur */
    double hauteur, largeur, longueur; /*hitbox*/
    double atk; /*attaque*/
    double reg; /*régenération*/
    double jetpack; /*jet pack*/
    double jetpack_max; /*jet pack*/
    int niv;
    int xp;
    double vit;
    double def;
    int seuil;
}s_joueur;

typedef s_joueur * joueur;

joueur creer_joueur(position pos);

void liberer_joueur(joueur j);

void utiliser_jetpack(joueur j);

void degat(int deg,joueur j);

void amelirorer_stat(joueur j,int stat,double val);

void niveau_suivant(joueur j);

#endif /*_JOUEUR_H_*/