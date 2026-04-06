#ifndef COMPOSANT2D_H
#define COMPOSANT2D_H

#include "GL/gl.h"
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include"config/config.h"
#include"moteur/interface.h"

#define POPUP_DURATION 2000

void draw_rect(float x, float y, float w, float h, float r, float g, float b, float a);

void draw_text(float x, float y, const char* text);

float get_text_width(const char* text);

void draw_text_underlined(float x, float y, const char* text);

void draw_text_color(float x, float y, const char* text, float r, float g, float b);

void draw_text_underlined_color(float x, float y, const char* text,float r, float g, float b);

void draw_circle(float cx, float cy, float r, int num_segments);

void draw_disk(float cx, float cy, float r, int num_segments);

void draw_colored_circle(float cx, float cy, float radius, int num_segments, float r_col, float g_col, float b_col);

void draw_colored_disk(float cx, float cy, float radius, int num_segments, float r_col, float g_col, float b_col);

void afficher_texte_centre(const char *texte, float x_centre, float y_centre, float scale, float r, float g, float b);

void afficher_popup(const char *popup_texte, int popup_fin_time,float r,float g,float b);

#endif