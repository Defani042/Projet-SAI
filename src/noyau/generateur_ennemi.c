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
    e2 = creer_ennemi(creer_objet(creer_position(2,0,0),1,1,1));
    e3 = creer_ennemi(creer_objet(creer_position(4,0,0),1,1,1));

    /*set e1 TANK*/
    e1->degat = 3;
    e1->vie = 50;
    e1->vit = 0.1;

    /*set e2 SOLDAT*/
    e2->degat = 5;
    e2->vie = 30;
    e2->vit = 0.2;

    /*set e2 SOLDAT*/
    e3->degat = 5;
    e3->vie = 15;
    e3->vit = 0.3;

    /*rangement dans le tableau*/
    globale_ennemi_tab[TANK] = e1;
    globale_ennemi_tab[SOLDAT] = e2;
    globale_ennemi_tab[ASSASIN] =e3;

    log_message(NOYAU SUCC "tableau des ennemi... OK");

} 

/*
R: création d'un ennemi aléatoire
E: vide
S: vide
A: Adrien
*/
ennemi creer_ennemi_alea(carte c){
    double nx,ny,nz;
    int s1,s2;
    int classe;
    joueur j;
    int ok =1;
    ennemi e;
    int essais = 0;
    objet col1,col2;

    if (!c || !c->j || !c->j->pos){
        log_message(NOYAU WARN "une des variables de départ de  creer_ennemi_alea() est NULL");
        return NULL;
    }
    j = c->j;

    
    /*génération de la classe entre 0 et 2*/
    classe = alea_int(0,2);
    /*création de l'ennemie de base*/
    e = creer_ennemi(creer_objet(creer_position(-9000,-9000,-9000),1,1,1));/*je les fais spawn hors de la map sinon dégat au joueur possible*/
    /*affectation des caractéristique de la classe*/
    e->degat = globale_ennemi_tab[classe]->degat;
    e->vie   = globale_ennemi_tab[classe]->vie;
    e->vit   = globale_ennemi_tab[classe]->vit; 
    e->classe = classe;
    while (ok && essais < 100)/*on test le spawn d'un ennemi 100 fois et si on n'arrive pas à le faire spawn on quitte*/
    {
        /*génération du signe pour x et y*/
        s1 = alea_int(0,1) ? 1 : -1; /* si aléa renvoie 1 s1 = 1 sinon -1*/
        s2 = alea_int(0,1) ? 1 : -1; /* si aléa renvoie 1 s2 = 1 sinon -1*/

        /*generation de la position aléatoire avec le signe*/
        nx = j->pos->x + alea_double(15,50) * s1;
        ny = j->pos->y + alea_double(15,50) * s2;
        nz = j->pos->z + alea_double(1,4);
      
        /*application de la position à l'ennemi*/
        e->obj->pos->x = nx; 
        e->obj->pos->y = ny;
        e->obj->pos->z = nz;

        /*test les collision*/
        col1 = detecter_collision_ennemi(grille_statique,e);
        col2 = detecter_collision_ennemi(grille_dynamique,e);

        if(col1 == NULL && col2 == NULL){
            ok = 0; /*l'ennemie spawn*/
        }
        essais++;
    }
    if (essais == 100) {
        log_message(NOYAU WARN "Spawn ennemi échoué aprés 100 essais");
        liberer_ennemi(e);  /* IMPORTANT libération de l'ennemi en mémoire pour éviter les fuite*/
        return NULL;
    }
    return e;

}


#endif /*_GENERATEUR_ENNEMI_C_*/