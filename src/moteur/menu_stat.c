#ifndef _MENU_STAT_C_
#define _MENU_STAT_C_

#include "moteur/menu_stat.h"
#include "config/config.h"

char statistique[NB_MAX];

/*
R: affiche le fenêtre du menu pause
E: rien
S: rien
A: Gaultier
*/
void afficher_fenetre_stat(joueur j){
    int ame_x = largeur_ecran/2+240;
    int ame_y = hauteur_ecran/2-250;

    draw_rect(ame_x,ame_y,230,500,0,0,0, 0.7f);
    draw_text_underlined_color(ame_x + 60,ame_y + 30, "Statistique",1,1,1);

    sprintf(statistique,"PV Max: %.0f", j->vie_max);
    draw_text_color(ame_x + 10,ame_y + 50 + 30, statistique,1,1,1);

    sprintf(statistique,"ATQ : %.0f", j->atk);
    draw_text_color(ame_x + 10,ame_y + 100 + 30,statistique,1,1,1);

    sprintf(statistique,"Defence : %.0f", j->def);
    draw_text_color(ame_x + 10,ame_y + 150 + 30, statistique,1,1,1);

    sprintf(statistique,"Regeneration pv : %.2f", j->reg_vie);
    draw_text_color(ame_x + 10,ame_y + 200 + 30, statistique,1,1,1);

    sprintf(statistique,"Regeneration jet : %.2f", j->reg_jetpack);
    draw_text_color(ame_x + 10,ame_y + 250 + 30, statistique,1,1,1);

    sprintf(statistique,"Jetpack max : %.2f", j->jetpack_max);
    draw_text_color(ame_x + 10,ame_y + 300 + 30, statistique,1,1,1);

    sprintf(statistique,"Taux crit : %d", j->taux_crit);
    draw_text_color(ame_x + 10,ame_y + 350 + 30, statistique,1,1,1);

    sprintf(statistique,"Degat crit : %d", j->degats_crit);
    draw_text_color(ame_x + 10,ame_y + 400 + 30, statistique,1,1,1);

    sprintf(statistique,"Vitesse : %.0f", j->vit);
    draw_text_color(ame_x + 10,ame_y + 450 + 30, statistique,1,1,1);

}

#endif /*_MENU_STAT_C_*/