#ifndef _GENERATEUR_ENNEMI_C_
#define _GENERATEUR_ENNEMI_C_

#include "noyau/generateur_ennemi.h"

ennemi globale_ennemi_tab[NB_TYPE_E];

/*
R: initialiser le tableau d'ennemis
E: vide
S: vide
A: Adrien
*/
void init_tab_ennemi(){
    ennemi e1,e2,e3;
    /*création des ennemi*/
    e1 = creer_ennemi(creer_objet(creer_position(0,0,0),1,1,1));
    e2 = creer_ennemi(creer_objet(creer_position(0,0,0),1,1,1));
    e3 = creer_ennemi(creer_objet(creer_position(0,0,0),1,1,1));

    /*set e1 TANK*/
    e1->degat = 3;
    e1->vie = 50;
    e1->vit = 0.5;

    /*set e2 SOLDAT*/
    e2->degat = 5;
    e2->vie = 30;
    e2->vit = 1.0;

    /*set e2 SOLDAT*/
    e3->degat = 5;
    e3->vie = 15;
    e3->vit = 1.0;

    /*rangement dans le tableau*/
    globale_ennemi_tab[TANK] = e1;
    globale_ennemi_tab[SOLDAT] = e2;
    globale_ennemi_tab[ASSASIN] =e3;

    log_message(NOYAU SUCC "tableau des ennemi... OK");

} 


#endif /*_GENERATEUR_ENNEMI_C_*/