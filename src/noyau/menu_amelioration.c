#ifndef _MENU_AMELIORATION_C_
#define _MENU_AMELIORATION_C_

#include "noyau/menu_amelioration.h"

void aff_fen_amelioration(){
    int ame_x = largeur_ecran/2-300;
    int ame_y = hauteur_ecran/2-250;
    draw_rect(ame_x,ame_y,600,500,0,0,0, 0.7f);
    draw_text_underlined_color(ame_x + 187,ame_y + 30, "Choisissez une amélioration !",1,1,1);
    draw_rect(ame_x + 100,ame_y + 70,400,100,0,0,0, 1.0f);
    draw_rect(ame_x + 100,ame_y + 210,400,100,0,0,0, 1.0f);
    draw_rect(ame_x + 100,ame_y + 360,400,100,0,0,0, 1.0f);
}

#endif /*_MENU_AMELIORATION_C_*/