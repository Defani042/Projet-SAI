#ifndef _COMPOSANT3D_H_
#define _COMPOSANT3D_H_

#include "GL/gl.h"
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

/*parite noyau*/
#include "noyau/objet.h"
#include "noyau/carte_globale.h"
#include "noyau/aleatoire.h"

void Parallelepiped(float x, float y, float z, float dx, float dy, float dz);

void afficher_objet_couleur(objet o);

void afficher_carte(carte c);

void afficher3d();


#endif /*_COMPOSANT3D_H_*/