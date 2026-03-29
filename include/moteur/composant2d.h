#ifndef COMPOSANT2D_H
#define COMPOSANT2D_H

#include "GL/gl.h"
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include"config/config.h"

void draw_rect(float x, float y, float w, float h, float r, float g, float b);

void draw_text(float x, float y, const char* text);

float get_text_width(const char* text);

void draw_text_underlined(float x, float y, const char* text);

void draw_text_color(float x, float y, const char* text, float r, float g, float b);

void draw_text_underlined_color(float x, float y, const char* text,float r, float g, float b);

void draw_circle(float cx, float cy, float r, int num_segments);

void draw_disk(float cx, float cy, float r, int num_segments);

void draw_colored_circle(float cx, float cy, float radius, int num_segments, float r_col, float g_col, float b_col);

void draw_colored_disk(float cx, float cy, float radius, int num_segments, float r_col, float g_col, float b_col);

#endif