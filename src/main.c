#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>

/*moteur du jeu*/
#include "moteur/affichage.h"
#include "moteur/controle.h"

/*log*/
#include "log/log.h"

/*noyau du jeu*/
#include "noyau/generateur_carte.h"
#include "noyau/carte_globale.h"

int main(int argc, char *argv[]){
    /*creation du fichier de log*/
    log_init();
    log_nettoyer();
    log_message(INIT SUCC "les fichiers de log ont été créés");
    log_message(INIT SUCC "Début du jeu");
    
    /*initialisation de la map*/
    carte_jeu = creer_carte_test();
    log_message(INIT SUCC "la carte a été créé");

    /*opengl*/
    glutInit(&argc, argv);                
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutInitWindowPosition(50, 50);  
    glutCreateWindow("Projet SAI");
    glutFullScreen();
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutDisplayFunc(affichage);   
    glutIdleFunc(animer);
    glutKeyboardFunc(touche_pressee);
    glutKeyboardUpFunc(touche_relachee);
    glutPassiveMotionFunc(mouvement_souris);
    glutMotionFunc(mouvement_souris);
    glutMainLoop();
    glutMainLoop();/*boucle principale*/

    /*fermeuture de la carte*/
    log_message(INIT SUCC "Fermeture du jeux");
    liberer_carte(carte_jeu);

    exit(EXIT_SUCCESS);
}