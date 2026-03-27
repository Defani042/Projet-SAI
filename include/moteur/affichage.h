#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "GL/gl.h"
#include "GL/glut.h"
#include "GL/freeglut_ext.h" 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

/*parite moteur*/
#include "moteur/interface.h"
#include "moteur/composant3d.h"

/*Variables globales*/
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

void gestion_signal(int sig);

void sortie_propre();

void fermer_fenetre();

void liberer_jeux();

void initialisation();

void animer();

void affichage();


#endif /*AFFICHAGE_H*/