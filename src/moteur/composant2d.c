#ifndef _COMPOSANT2D_C_
#define _COMPOSANT2D_C_

#include "moteur/composant2d.h"
/*
R: permet d'afficher un rectangle
E: 7 float (les coordonné x,y)(la taille w et h)(les rgb)
S: rien
A: Adrien
*/
void draw_rect(float x, float y, float w, float h, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

/*
R: permet d'afficher du texte
E: 2 float (les coordonné x,y) et une chaine de caractère
S: rien
A: Adrien
*/
void draw_text(float x, float y, const char* text)
{
    glColor3f(1.0f, 1.0f, 1.0f); /*couleur blanc*/
    glRasterPos2f(x, y);         /*position*/
    /*affichage du texte*/
    while (*text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}

#endif /*_COMPOSANT2D_C_*/