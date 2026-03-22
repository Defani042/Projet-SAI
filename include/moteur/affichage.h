#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "GL/gl.h"
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Variables globales*/
extern int xO;
extern int yO;
extern int zO;
extern int eyeX;
extern int eyeY;
extern int eyeZ;
extern int upX;
extern int upY;
extern int upZ;
extern int l;
extern int r;
extern int b;
extern int top;
extern int n;
extern int f;

void drawParallelepiped(float x, float y, float z, float dx, float dy, float dz);

void animer();

void affichage();

#endif /*AFFICHAGE_H*/