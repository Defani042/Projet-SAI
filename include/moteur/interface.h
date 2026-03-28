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

extern clock_t timer;

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

void afficher_interface();

#endif /*_INTERFACE_H_*/