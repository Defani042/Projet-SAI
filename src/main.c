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
    int tj,to,tm;
    int size;
    char buff1[64];
    char buff2[64];
    char buff3[64];
    char buff4[64];
    srand((unsigned int)time(NULL));

    /*creation du fichier de log*/
    log_init();
    log_nettoyer();
    log_message(INIT SUCC "les fichiers de log ont été créés");
    log_message(INIT SUCC "Début du jeu");
    
    /*initialisation de la map*/
    carte_jeu = creer_carte_test();
    log_message(INIT SUCC "la carte a été créé");

    /*calcul des resource consommer par la carte*/
    tj = sizeof(joueur);
    size  =  taille(carte_jeu->liste_objets);
    to = sizeof(objet) * size;
    tm = sizeof(carte) + to;

    /*préparation du message pour les log */
    sprintf(buff1,"%s%s taille de la structure carte %d octets",INIT,SUCC,tm);
    sprintf(buff2,"%s%s taille de la structure joueur %d octets",INIT,SUCC,tj);
    sprintf(buff3,"%s%s taille de la liste d'objets %d octets",INIT,SUCC,to);
    sprintf(buff4,"%s%s nombre d'objet initialisés %d ",INIT,SUCC,size);

    /*écriture dans les log*/
    log_message(INIT SUCC"====MONITEUR====");
    log_message(buff1);
    log_message(buff2);
    log_message(buff3);
    log_message(buff4);
    log_message(INIT SUCC"================");
    log_message(INIT SUCC"Préparation du rendu OPENGL");

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