#ifndef _COMPOSANT3D_H_
#define _COMPOSANT3D_H_

#include "GL/gl.h"
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

extern int nb_obj;
extern float angle_soleil;

/*parite noyau*/
#include "noyau/objet.h"
#include "noyau/carte_globale.h"
#include "noyau/aleatoire.h"
#include "moteur/interface.h"

void Parallelepiped(float x, float y, float z, float dx, float dy, float dz);

void afficher_objet_couleur(objet o);

void afficher_carte(carte c);

void sphere(float x, float y, float z, float radius, float r, float g, float b);

void afficher_cercle3D(position c, float radius);

objet creer_arbre(int x, int y, int z);

objet creer_rocher(int x, int y, int z);

objet creer_maison(int x, int y, int z);

void afficher_hitbox_joueur(joueur j);

void afficher3d();



#endif /*_COMPOSANT3D_H_*/