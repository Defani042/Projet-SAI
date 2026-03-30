#ifndef _GRILLE_H_
#define _GRILLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noyau/objet.h"
#include "noyau/ennemi.h"


typedef struct s_grille {
    int taille_x;          /*Taille en X de la grille*/
    int taille_y;          /*Taille en Y de la grille*/
    double cell_size;      /*Taille d'une cellule en unité du monde*/
    objet** objets;        /*Tableau 2D d'objets, chaque case contient une liste chaînée d'objets*/
} s_grille;

typedef s_grille * grille;

grille creer_grille(int taille_x, int taille_y,double cell_size);

void detruire_grille(grille g);

void vider_grille(grille g) ;

int coord_to_cell_x(double pos, grille g);

int coord_to_cell_y(double pos, grille g);

void remplir_grille_statique(grille g, objet liste_objets);

void remplir_grille_dynamique(grille g, ennemi liste_ennemis);

void afficher_grille(grille g);

void afficher_grille_log(grille g);


#endif /*_GRILLE_H_*/