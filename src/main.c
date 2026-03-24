#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <time.h> 

/*moteur du jeu*/
#include "moteur/affichage.h"
#include "moteur/controle.h"

/*log*/
#include "log/log.h"

/*noyau du jeu*/
#include "noyau/generateur_carte.h"
#include "noyau/carte_globale.h"

int main(int argc, char *argv[]){

    srand((unsigned int)time(NULL));
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
    initialisation();
    glutMainLoop();/*boucle principale*/

    /*fermeuture de la carte*/
    log_message(INIT SUCC "Fermeture du jeux");
    liberer_carte(carte_jeu);
    glutMainLoop();
    
    exit(EXIT_SUCCESS);
}