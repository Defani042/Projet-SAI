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


int deja_libere = 0;
/*
R: libération du jeusx
E: une chaine de caractere
S: rien
A: Adrien
*/
void liberer_jeux(){
   
    if (deja_libere) return; /*portection*/
    /*zone de la meme à libérrer*/
    liberer_carte(carte_jeu);
    carte_jeu = NULL;
    log_close();

    
   
}
/*
R: écriture dans les fichier de log
E: une chaine de caractere
S: rien
A: Adrien
*/
void fermer_fenetre() {
    log_message(INIT SUCC "Fermeture de la fenêtre...");
    liberer_jeux();
}
/*
R: écriture dans les fichier de log
E: une chaine de caractere
S: rien
A: Adrien
*/
void liberation_programme(int sig){
    char buffer[128];
    switch(sig) {
        case SIGINT:
            log_message(INIT SUCC"Signal SIGINT reçu. Nettoyage..." );
            break;
        case SIGTERM:
            log_message(INIT SUCC"Signal SIGTERM reçu. Nettoyage...");
            break;
        case SIGSEGV:
            log_message(INIT SUCC"Signal SIGSEV reçu. Nettoyage...");
            log_message(INIT SUCC"Erreur de ségmentation...");
            break;        
        default:
            sprintf(buffer, INIT SUCC"Signal %d reçu. Nettoyage...", sig);
            log_message(buffer);
    }
    liberer_jeux();
    exit(EXIT_SUCCESS);/*car la mémoir est libérer donc c'est nice*/
}

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
    

    /*init timer*/
    timer = clock();
    log_message(INIT SUCC "timer initialisé");
    /*initialisation de la map*/
    carte_jeu = creer_carte_jeu();
    log_message(INIT SUCC "la carte a été créé");

    /*calcul des resource consommer par la carte*/
    tj = sizeof(s_joueur);
    size  =  taille(carte_jeu->liste_objets);
    to = sizeof(s_objet) * size;
    tm = sizeof(s_carte) + tj + to;
    /*signalisation*/
    signal(SIGINT, liberation_programme);
    signal(SIGTERM, liberation_programme);
    signal(SIGSEGV, liberation_programme);
    log_message(INIT SUCC "signalisation... OK");
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
    /*callback quand on ferme la fenêtre*/
    glutCloseFunc(fermer_fenetre);
    glutMainLoop();/*boucle principale*/
    exit(EXIT_SUCCESS);
}