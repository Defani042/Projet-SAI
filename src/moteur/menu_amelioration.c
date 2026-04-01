#ifndef _MENU_AMELIORATION_C_
#define _MENU_AMELIORATION_C_

#include "moteur/menu_amelioration.h"
#include "moteur/menu_stat.h"
#include "noyau/joueur.h"
#include "noyau/carte_globale.h"
#include "noyau/aleatoire.h"
#include "config/config.h"

char* nom_stat[8] = {
    "Defence",
    "Point de vie",
    "Attaque",
    "Regeneration de pv",
    "Point de jetpack",
    "Vitesse",
    "Taux critique",
    "Degats critique"
};

char description1[NB_MAX];
char description2[NB_MAX];
char description3[NB_MAX];

int stat_competence1;
int stat_competence2;
int stat_competence3;

int val1;
int val2;
int val3;

int choix_valeur(int comp){
    switch(comp){
        case CAP_DEF: return alea_int(1,3);
        case CAP_VIE: return alea_int(5,15);
        case CAP_ATK: return alea_int(1,3);
        case CAP_REG: return alea_int(1,2);
        case CAP_JET: return alea_int(1,3);
        case CAP_VIT: return alea_int(1,3);
        case CAP_TAUX_CRIT: return alea_int(2,7);
        default: return alea_int(5,15);
    }
}

void choix_competence(){

    stat_competence1 = alea_int(CAP_DEF, CAP_DEGATS_CRIT);

    stat_competence2 = alea_int(CAP_DEF, CAP_DEGATS_CRIT - 1);
    if(stat_competence2 >= stat_competence1) stat_competence2++;

    stat_competence3 = alea_int(CAP_DEF, CAP_DEGATS_CRIT - 2);
    if(stat_competence3 == stat_competence1) stat_competence3++;
    if(stat_competence3 == stat_competence2) {
        stat_competence3++;
        if(stat_competence3 == stat_competence1) {
            stat_competence3++;
            stat_competence3 = stat_competence3% CAP_DEGATS_CRIT + 1;
        }
    }
    val1 = choix_valeur(stat_competence1);
    val2 = choix_valeur(stat_competence2);
    val3 = choix_valeur(stat_competence3); 
    
    sprintf(description1,"La stat %s augmente de %d",nom_stat[stat_competence1],val1);
    sprintf(description2,"La stat %s augmente de %d",nom_stat[stat_competence2],val2);
    sprintf(description3,"La stat %s augmente de %d",nom_stat[stat_competence3],val3);
}

/*
R: affiche le fenêtre du menu
E: rien
S: rien
A: Gaultier
*/
void afficher_fenetre_amelioration(){
    int ame_x = largeur_ecran/2-370;
    int ame_y = hauteur_ecran/2-250;

    afficher_fenetre_stat(carte_jeu->j);

    draw_rect(ame_x,ame_y,600,500,0,0,0, 0.7f);
    draw_text_underlined_color(ame_x + 187,ame_y + 30, "Choisissez une amélioration !",1,1,1);
    draw_rect(ame_x + 100,ame_y + 70,400,100,0,0,0, 1.0f);
    draw_rect(ame_x + 100,ame_y + 210,400,100,0,0,0, 1.0f);
    draw_rect(ame_x + 100,ame_y + 360,400,100,0,0,0, 1.0f);
    draw_text_underlined_color(ame_x + 140,ame_y + 125, description1,1,0,0);
    draw_text_underlined_color(ame_x + 140,ame_y + 265, description2,0,1,0);
    draw_text_underlined_color(ame_x + 140,ame_y + 415, description3,0,0,1);
}

#endif /*_MENU_AMELIORATION_C_*/