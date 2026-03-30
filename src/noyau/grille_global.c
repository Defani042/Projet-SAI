#ifndef _GRILLE_GLOBAL_C_
#define _GRILLE_GLOBAL_C_

#include "noyau/grille_global.h"


/* Définition des variables globales */
grille grille_statique = NULL;
grille grille_dynamique = NULL;


void maj_grille_dynamique(ennemi liste_ennemis) {
    vider_grille(grille_dynamique);
    remplir_grille_dynamique(grille_dynamique, liste_ennemis);
    /*log_message(NOYAU SUCC "Grille dynamique mise à jour");*/
    
    printf("GRILLE DYNAMIQUE:\n");
    afficher_grille(grille_dynamique);
    /*printf("GRILLE STATIQUE:\n");
    afficher_grille(grille_statique);*/
    
    }


#endif /*CARTE_GLOBALE_C_*/