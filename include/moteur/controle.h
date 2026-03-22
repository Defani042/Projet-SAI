#ifndef CONTROLE_H
#define CONTROLE_H

#include "GL/gl.h"
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>

#include "moteur/affichage.h"

extern float cameraFrontX;
extern float cameraFrontY; 
extern float cameraFrontZ;

void avancer();

void gauche();

void reculer();

void droite();

void haut();

void bas();

void clavier_down(unsigned char touche, int x, int y);

void clavier_up(unsigned char touche, int x, int y);

void raffraichir();

void gerer_souris(int bouton, int etat, int x, int y);

void mouvement_souris(int x, int y);

#endif /*CONTROLE_H*/