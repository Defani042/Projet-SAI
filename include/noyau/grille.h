#ifndef _GRILLE_H_
#define _GRILLE_H_

#include <stdio.h>
#include <stdlib.h>
#include "noyau/objet.h"
#include "noyau/ennemi.h"


typedef struct s_cellule {
    objet liste; /* liste chaînée d'objets présents dans cette cellule*/
}s_cellule;

typedef s_cellule * cellule;

typedef struct s_grille {
    int taille_x;
    int taille_y;
    double cell_size; /*taille d'une cellule en unité du monde*/
    cellule** cellules; /*tableau 2D [taille_x][taille_y]*/
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


#endif /*_GRILLE_H_*/