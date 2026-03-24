#ifndef COMPOSANT2D_H
#define COMPOSANT2D_H

#include "GL/gl.h"
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>

void draw_rect(float x, float y, float w, float h, float r, float g, float b);

void draw_text(float x, float y, const char* text);

#endif