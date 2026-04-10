#ifndef CONTROLE_H
#define CONTROLE_H

#include "GL/gl.h"
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>


/*partie moteur*/
#include "moteur/affichage.h"
#include "moteur/menu_amelioration.h"
/*partie noyau*/
#include "noyau/deplacement.h"
#include "noyau/carte_globale.h"

extern float positionX;
extern float positionY;
extern float directionX;
extern float directionY;
extern float directionZ;
extern int competence;
extern int interruption;

void avancer();

void gauche();

void reculer();

void droite();

void haut();

void bas();

void show_debug_menu();

void show_menu_upgrade();

void show_menu_mort();

void touche_pressee(unsigned char touche, int x, int y);

void touche_relachee(unsigned char touche, int x, int y);

void raffraichir();

void gerer_souris(int bouton, int etat, int x, int y);

void mouvement_souris(int x, int y);

#endif /*CONTROLE_H*/