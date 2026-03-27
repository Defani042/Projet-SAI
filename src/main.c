#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <time.h> 
#include <signal.h>

/*moteur du jeu*/
#include "moteur/affichage.h"
#include "moteur/controle.h"

/*log*/
#include "log/log.h"

/*noyau du jeu*/
#include "noyau/generateur_carte.h"
#include "noyau/carte_globale.h"

int main(int argc, char *argv[]){
    int tj,to,tm,te;
    int size1,size2;
    char buff1[64];
    char buff2[64];
    char buff3[64];
    char buff4[64];
    char buff5[64];
    char buff6[64];
    srand((unsigned int)time(NULL));

    /*creation du fichier de log*/
    log_init();
    log_nettoyer();
    log_message(INIT SUCC "les fichiers de log ont été créés");
    log_message(INIT SUCC "Début du jeu");
    

    /*init timer*/
    timer = clock();
    log_message(INIT SUCC "timer initialisé");
    /*initialisation de la map*/
    carte_jeu = creer_carte_jeu();
    log_message(INIT SUCC "la carte a été créé");

    /*calcul des resource consommer par la carte*/
    tj = sizeof(s_joueur);
    size1  =  taille_objet(carte_jeu->liste_objets);
    to = sizeof(s_objet) * size1;
    size2 =  taille_ennemi(carte_jeu->liste_ennemi);
    te = sizeof(s_ennemi)*size2;
    tm = sizeof(s_carte) + tj + to + te;
    /*signalisation*/
    signal(SIGINT, sortie_propre);
    signal(SIGTERM, sortie_propre);
    signal(SIGSEGV, sortie_propre);
    log_message(INIT SUCC "signalisation... OK");
    /*préparation du message pour les log */
    sprintf(buff1,"%s%s taille de la structure carte %d octet(s)",INIT,SUCC,tm);
    sprintf(buff2,"%s%s taille de la structure joueur %d octet(s)",INIT,SUCC,tj);
    sprintf(buff3,"%s%s taille de la liste d'objets %d octet(s)",INIT,SUCC,to);
    sprintf(buff4,"%s%s taille de la liste d'ennemis %d octet(s)",INIT,SUCC,te);
    sprintf(buff5,"%s%s nombre d'objet(s) initialisés  : %d ",INIT,SUCC,size1);
    sprintf(buff6,"%s%s nombre d'ennemi(s) initialisés : %d ",INIT,SUCC,size2);
    /*écriture dans les log*/
    log_message(INIT SUCC"====MONITEUR====");
    log_message(buff1);
    log_message(buff2);
    log_message(buff3);
    log_message(buff4);
    log_message(buff5);
    log_message(buff6);
    log_message(INIT SUCC"================");
    log_message(INIT SUCC"Préparation du rendu OPENGL");

    /*opengl*/
    glutInit(&argc, argv);                
    initialisation();
    /*callback quand on ferme la fenêtre*/
    glutCloseFunc(fermer_fenetre);
    glutMainLoop();/*boucle principale*/
    exit(EXIT_SUCCESS);
}