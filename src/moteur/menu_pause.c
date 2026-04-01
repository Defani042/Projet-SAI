#ifndef _MENU_PAUSE_C_
#define _MENU_PAUSE_C_

#include "moteur/menu_pause.h"
#include "moteur/menu_stat.h"
#include "noyau/joueur.h"
#include "noyau/carte_globale.h"

/*
R: affiche le fenêtre du menu pause
E: rien
S: rien
A: Gaultier
*/
void afficher_fenetre_pause(){
    int ame_x = largeur_ecran/2-370;
    int ame_y = hauteur_ecran/2-250;

    afficher_fenetre_stat(carte_jeu->j);

    draw_rect(ame_x,ame_y,600,500,0,0,0, 0.7f);
    draw_text_underlined_color(ame_x + 275,ame_y + 30, "Pause",1,1,1);

    draw_rect(ame_x + 120,ame_y + 300,120,50,0,0,1.0f, 1.0f);
    draw_text_color(ame_x + 137,ame_y + 332, "Continuer",1,1,1);

    draw_rect(ame_x + 362,ame_y + 300,120,50,1.0f,0,0, 1.0f);
    draw_text_color(ame_x + 392,ame_y + 332, "Quitter",1,1,1);

}

#endif /*_MENU_PAUSE_C_*/