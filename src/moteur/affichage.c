#ifndef AFFICHAGE_C
#define AFFICHAGE_C

#include "moteur/controle.h"
#include <time.h>

/*variables globales*/
int xO = -71;
int yO = -41;
int zO = 2;
int eyeX = -11;
int eyeY = -41;
int eyeZ = 2;
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
    static clock_t last_time = 0;
    clock_t current_time = clock();
    if (!(current_time - last_time < CLOCKS_PER_SEC / 60)){
        last_time = current_time;
        raffraichir();
        glutPostRedisplay();
    }
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
    gluLookAt(eyeX,eyeY,eyeZ,eyeX + cameraFrontX,eyeY + cameraFrontY,eyeZ + cameraFrontZ,upX,upY,upZ);

    /*Definition des points*/
    glBegin(GL_QUADS); /*GL_POINTS affiche des points et GL_QUADS affiche des rectangles*/

    /*Zone d'affichage*/
    drawParallelepiped(-40,-40,-5,40,40,5);

    /*printf("ex,ey,ez,xO,y0,z0 : %d,%d,%d,%d,%d,%d\n", eyeX,eyeY,eyeZ,xO,yO,zO);*/

    glEnd();

    /*Fin*/
    glutSwapBuffers();
}

#endif /*AFFICHAGE_C*/