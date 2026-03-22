#include <stdio.h>
#include <stdlib.h>

#include "moteur/affichage.h"
#include "moteur/controle.h"

int main(int argc, char *argv[]){
    glutInit(&argc, argv);                
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);  
    glutCreateWindow("Projet SAI");
    glutFullScreen();
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutDisplayFunc(affichage);   
    glutIdleFunc(animer);
    glutKeyboardFunc(clavier_down);
    glutKeyboardUpFunc(clavier_up);
    glutPassiveMotionFunc(mouvement_souris);
    glutMainLoop();
    exit(EXIT_SUCCESS);
}