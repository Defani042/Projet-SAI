#ifndef CONTROLE_H
#define CONTROLE_H

#include "GL/gl.h"
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>

#include "moteur/affichage.h"

extern float directionX;
extern float directionY; 
extern float directionZ;

void avancer();

void gauche();

void reculer();

void droite();

void haut();

void bas();

void touche_pressee(unsigned char touche, int x, int y);

void touche_relachee(unsigned char touche, int x, int y);

void raffraichir();

void gerer_souris(int bouton, int etat, int x, int y);

void mouvement_souris(int x, int y);

#endif /*CONTROLE_H*/