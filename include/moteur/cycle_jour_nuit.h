#ifndef _CYCLE_JOUR_NUIT_H_
#define _CYCLE_JOUR_NUIT_H_

#include "GL/gl.h"
#include "GL/glut.h"
#include "GL/freeglut_ext.h" 
#include <math.h>

#include "moteur/composant3d.h"
#include "noyau/generateur_carte.h"

void calcul_couleur(float t,float r1, float g1, float b1,float r2, float g2, float b2,float *r, float *g, float *b);

void cycle_jour_nuit();

#endif /* _CYCLE_JOUR_NUIT_H_ */