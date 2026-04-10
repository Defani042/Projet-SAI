#ifndef _MENU_MORT_C_
#define _MENU_MORT_C_

#include "moteur/menu_mort.h"

char buffer[NB_MAX];
int aff_message = 1;

void afficher_fenetre_mort(joueur j){
    if (j->vie < 0) j->vie = 0; /*pour éviter les valeurs négatives dans les statistiques*/
    /* Affichage de la fenêtre de mort avec les statistiques du joueur */
    if(aff_message){
        sprintf(buffer,NOYAU"=== Vous êtes mort ===\n");
        log_message(buffer);
        sprintf(buffer,NOYAU"Vie finale : %.2f\n", j->vie);
        log_message(buffer);
        sprintf(buffer,NOYAU"Jetpack final : %.2f\n", j->jetpack);
        log_message(buffer);
        sprintf(buffer,NOYAU"Niveau atteint : %d\n", j->niv);
        log_message(buffer);
        sprintf(buffer,NOYAU"XP total : %d\n", j->xp);
        log_message(buffer);
        sprintf(buffer,NOYAU"Merci d'avoir joué !\n");
        log_message(buffer);
        aff_message = 0;
    }

    draw_rect(0,0,largeur_ecran,hauteur_ecran,0,0,0, 1.0f);
    afficher_fenetre_stat(j);
    draw_text_underlined_color(largeur_ecran/3 - 50, 200, "Fin de Partie",1,0,0);

    draw_text_underlined_color(largeur_ecran/3 - 60, 250, "Vous etes mort",1,0,0);
    sprintf(buffer,"Nombre d'elimination : %d",nbkill);
    draw_text_color(largeur_ecran/3 - 90, 300, buffer,1,0,0);
    sprintf(buffer,"Niveau de difficulte : %d",difficulte);
    draw_text_color(largeur_ecran/3 - 85, 350, buffer,1,1,0);
    draw_text_color(largeur_ecran/3 - 80, 400, "Cliquez pour quitter",1,1,1);

}

#endif /*_MENU_MORT_C_*/