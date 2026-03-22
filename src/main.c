#include <stdio.h>
#include <stdlib.h>

/*moteur du jeu*/
#include "moteur/affichage.h"
#include "moteur/controle.h"

/*noyau du jeu*/
#include "noyau/generateur_carte.h"

int main(int argc, char *argv[]){
    carte c;
    printf("Debut du jeux\n");
    c = creer_carte_test();
    printf("Carte test créer\n");
    if(c == NULL){
        printf("ERREUR la carte est NULL\n");
        exit(EXIT_FAILURE);
    }
    printf("Carte test OK\n");

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