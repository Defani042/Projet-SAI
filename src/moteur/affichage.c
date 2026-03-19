#ifndef AFFICHAGE_C
#define AFFICHAGE_C

#include "moteur/controle.h"

/*variables globales*/
int xO = 0;
int yO = 0;
int zO = 0;
int eyeX = 60;
int eyeY = 60;
int eyeZ = 60;
int upX = 0;
int upY = 0;
int upZ = 1;
int l = -5;
int r = 5;
int b = -5;
int top = 5;
int n = 5;
int f = 1000;

/*
R: permet de dessiner un parallepipede
E: les coordonnées du parralepipède
S: rien
A: Gaultier
*/
void drawParallelepiped(float x, float y, float z, float dx, float dy, float dz) {
    float hx = dx / 2.0f;
    float hy = dy / 2.0f;
    float hz = dz / 2.0f;
    
    /*Face avant (z +)*/
    glVertex3f(x - hx, y - hy, z + hz);
    glVertex3f(x + hx, y - hy, z + hz);
    glVertex3f(x + hx, y + hy, z + hz);
    glVertex3f(x - hx, y + hy, z + hz);

    /*Face arrière (z -)*/
    glVertex3f(x - hx, y - hy, z - hz);
    glVertex3f(x - hx, y + hy, z - hz);
    glVertex3f(x + hx, y + hy, z - hz);
    glVertex3f(x + hx, y - hy, z - hz);

    /*Face gauche (x -)*/
    glVertex3f(x - hx, y - hy, z - hz);
    glVertex3f(x - hx, y - hy, z + hz);
    glVertex3f(x - hx, y + hy, z + hz);
    glVertex3f(x - hx, y + hy, z - hz);

    /*Face droite (x +)*/
    glVertex3f(x + hx, y - hy, z - hz);
    glVertex3f(x + hx, y + hy, z - hz);
    glVertex3f(x + hx, y + hy, z + hz);
    glVertex3f(x + hx, y - hy, z + hz);

    /*Face haut (y +)*/
    glVertex3f(x - hx, y + hy, z - hz);
    glVertex3f(x - hx, y + hy, z + hz);
    glVertex3f(x + hx, y + hy, z + hz);
    glVertex3f(x + hx, y + hy, z - hz);

    /*Face bas (y -)*/
    glVertex3f(x - hx, y - hy, z - hz);
    glVertex3f(x + hx, y - hy, z - hz);
    glVertex3f(x + hx, y - hy, z + hz);
    glVertex3f(x - hx, y - hy, z + hz);
}

/*
R: permet d'actualiser les images
E: rien
S: rien
A: Gaultier
*/
void animer(){
    glutPostRedisplay();
}

/*
R: permet d'afficher les images
E: rien
S: rien
A: Gaultier
*/
void affichage(){
    /*debut*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*Modif de la visualisation*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(l,r,b,top,n,f);

    /*Init de la matrice de visualisation*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,xO,yO,zO,upX,upY,upZ);

    /*Definition des points*/
    glBegin(GL_QUADS); /*GL_POINTS affiche des points et GL_QUADS affiche des rectangles*/

    /*Zone d'affichage*/
    drawParallelepiped(-40,-40,-5,40,40,5);

    glutKeyboardFunc(gerer_clavier);

    glEnd();

    /*Fin*/
    glutSwapBuffers();
}

#endif /*AFFICHAGE_C*/