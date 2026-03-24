#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "GL/gl.h"
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

/*parite moteur*/
#include "moteur/interface.h"
/*parite noyau*/
#include "noyau/objet.h"
#include "noyau/carte_globale.h"
#include "noyau/aleatoire.h"

/*Variables globales*/
extern int xO;
extern int yO;
extern int zO;
extern float eyeX;
extern float eyeY;
extern float eyeZ;
extern int upX;
extern int upY;
extern int upZ;
extern int l;
extern int r;
extern int b;
extern int top;
extern int n;
extern int f;
extern int largeur_ecran;
extern int hauteur_ecran;

void initialisation();

void Parallelepiped(float x, float y, float z, float dx, float dy, float dz);

void animer();

void afficher_objet_couleur(objet o);

void affichage();

void afficher_carte(carte c);

#endif /*AFFICHAGE_H*/