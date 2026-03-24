#ifndef _INTERFACE_H_
#define _INTERFACE_H_

/*lib std*/
#include <stdio.h>
#include <stdlib.h>

#include "GL/gl.h"
#include "GL/glut.h"
#include "moteur/affichage.h"

void draw_rect(float x, float y, float w, float h, float r, float g, float b);

void afficher_vie();

void afficher_interface();

#endif /*_INTERFACE_H_*/