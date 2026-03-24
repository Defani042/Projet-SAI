#ifndef _JOUEUR_C_
#define _JOUEUR_C_

#include"noyau/joueur.h"


/*
R: création d'un joueur
E: 1 TAD position
S: 1 TAD joueur
A: Adrien
*/
joueur creer_joueur(position pos) {
    joueur j = NULL;
    if ((j = (joueur)malloc(sizeof(s_joueur))) == NULL)
	{
        fprintf(stderr,"Erreur malloc par la fonction creer_joueur()\n");
        log_message(NOYAU ERR "Erreur malloc par la fonction creer_joueur()");
        exit(EXIT_FAILURE);
    }
    j->dir = creer_position(1,0,0);
    j->atk = ATK;
    j->jetpack = JET;
    j->jetpack_max = JET;
    j->niv = 0;
    j->xp = 0;
    j->vie = VIE;
    j->vie_max = VIE;
    j->pos = pos;
    j->vit = DEFAULT;
    j->def = DEFAULT;
    j->seuil = SEUIL;

    j->hauteur = HAUT;
    j->largeur = LARG;
    j->longueur = LONG;
    log_message(NOYAU SUCC "Joueur créé");
    return j;
}

/*
R: libération d'un joueur en mémoire
E: 1 TAD joueur
S: vide
A: Adrien
*/
void liberer_joueur(joueur j){
    
    if(j != NULL){
        liberer_position(j->pos);
        free(j);
        j = NULL;
    }
    log_message(NOYAU SUCC "Joueur libéré");
}

/*
R: gestion de l'utilisation du jet pack
E: 1 TAD joueur 
S: vide
A: Adrien
*/
void utiliser_jetpack(joueur j){
     if(j == NULL){
        log_message(NOYAU WARN "Joueur NULL! fonction utiliser_jetpack()");
        return;
    }
    j->jetpack -= USE_JET_PACK;
}
/*
R: regeneration du jetpack
E: 1 TAD joueur 
S: vide
A: Adrien
*/
void regeneration_jetpack(joueur j){
    if(j->jetpack+USE_JET_PACK>j->jetpack_max){
        j->jetpack = j->jetpack_max;
    }
}

/*
R: gestion des dégats subit par le joueur
E: 1 TAD joueur 
S: vide
A: Adrien
*/
void degat(int deg,joueur j){
     if(j == NULL){
        log_message(NOYAU WARN "Joueur NULL! fonction degat()");
        return;
    }
    j->vie -= deg/j->def;
}


/*
R: fonction d'amelioration des stats du joueur 
E: 1 TAD joueur 1 entier (INDEXE DE LA STATS) 1 double (valueur d'augmentation) 
S: vide
A: Adrien
*/
void amelirorer_stat(joueur j,int stat,double val){
    if(j == NULL){
        log_message(NOYAU WARN "Joueur NULL! fonction améliorer_stats()");
        return;
    }
    switch (stat)
    {
    case CAP_ATK:j->atk += val;break;
    case CAP_DEF:j->def += val;break;
    case CAP_JET:j->jetpack_max += val;break;
    case CAP_REG:j->reg += val;break;
    case CAP_VIE:j->vie_max += val;break;
    case CAP_VIT:j->vit += val;break;
    default:break;
    }
}

/*
R: fonction de gestion du niveau des joueur 
E: 1 TAD joueur 
S: vide
A: Adrien
*/
void niveau_suivant(joueur j){
    if(j->xp <= j->niv*j->seuil){
        j->xp -= j->seuil*j->niv;
        j->niv++;
        j->seuil*=2;
    }
}




#endif /*_JOUEUR_C_*/