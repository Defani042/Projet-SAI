#ifndef _MENU_AMELIORATION_C_
#define _MENU_AMELIORATION_C_

#include "moteur/menu_amelioration.h"

char *description1;
char *description2;
char *description3;

/*
R: affiche le fenêtre du menu
E: rien
S: rien
A: Gaultier
*/
void aff_fen_amelioration(){
    int ame_x = largeur_ecran/2-300;
    int ame_y = hauteur_ecran/2-250;

    /*test*/
    description1 = "+ 20% PV";
    description2 = "+ 20% DEF";
    description3 = "+ 20% ATQ";
    /*fin test*/

    draw_rect(largeur_ecran - 20, 0, 20, 20, 1,0,0,1);
    draw_text_color(largeur_ecran - 15, 15, "x",1,1,1);
    draw_rect(ame_x,ame_y,600,500,0,0,0, 0.7f);
    draw_text_underlined_color(ame_x + 187,ame_y + 30, "Choisissez une amélioration !",1,1,1);
    draw_rect(ame_x + 100,ame_y + 70,400,100,0,0,0, 1.0f);
    draw_rect(ame_x + 100,ame_y + 210,400,100,0,0,0, 1.0f);
    draw_rect(ame_x + 100,ame_y + 360,400,100,0,0,0, 1.0f);
    draw_text_underlined_color(ame_x + 187,ame_y + 125, description1,1,0,0);
    draw_text_underlined_color(ame_x + 187,ame_y + 265, description2,0,1,0);
    draw_text_underlined_color(ame_x + 187,ame_y + 415, description3,0,0,1);
}

#endif /*_MENU_AMELIORATION_C_*/