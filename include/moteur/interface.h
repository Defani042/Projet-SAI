#ifndef _INTERFACE_H_
#define _INTERFACE_H_

/*lib std*/
#include <stdio.h>
#include <stdlib.h>

#include "GL/gl.h"
#include "GL/glut.h"

/*partie moteur*/
#include "moteur/composant2d.h"
#include "moteur/affichage.h"

/*partie noyau*/
#include "noyau/deplacement.h"

extern clock_t timer;
extern int show_menu_debug;
extern int aff_amelioration;
extern int aff_pause;

void afficher_vie();

void maj_fps();

void afficher_fps();

void afficher_xp(int screen_width);

void maj_fps();

void afficher_fps();

void afficher_pos();

void afficher_nb_obj();

void afficher_timmer();

void afficher_nb_ennemie();

void afficher_position_grille();

void afficher_menu_debug();

void afficher_kill();

void afficher_interface();

#endif /*_INTERFACE_H_*/