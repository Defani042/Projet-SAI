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
        exit(EXIT_FAILURE);
    }
    j->atk = ATK;
    j->jetpack = JET;
    j->niv = 0;
    j->xp = 0;
    j->vie = VIE;
    j->vie_max = VIE;
    j->pos = pos;
    j->vit = DEFAULT;
    j->def = DEFAULT;
    j->seuil = SEUIL;
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
}

/*
R: Déplacement d'un joueur dans l'espace
E: 1 TAD joueur et 3 double (les direction sur les axe X,Y et Z)
S: vide
A: Adrien
*/
void deplacement(joueur j,double dirx,double diry,double dirz){
    double nx,ny,nz,norme;
    if (j == NULL || j->pos == NULL) {
        fprintf(stderr, "Erreur : joueur ou position NULL dans deplacement()\n");
        return;
    }

    /*calcul de la norme */
    norme = sqrt(dirx*dirx + diry*diry + dirz*dirz);
    /*pas de déplacement on return*/
    if (norme == 0) {
        return;
    }
    /*normalisation*/
    nx = dirx / norme;
    ny = diry / norme;
    nz = dirz / norme;
    /*Déplacement*/
    j->pos->x += nx * j->vie;
    j->pos->y += ny * j->vie;
    j->pos->z += nz * j->vie;
}

/*
R: gestion de l'utilisation du jet pack
E: 1 TAD joueur 
S: vide
A: Adrien
*/
void utiliser_jetpack(joueur j){
     if(j == NULL){
        fprintf(stderr,"erreur dans la fonction utiliser_jetpack() le joueur est NULL\n");
        return;
    }
    j->jetpack -= USE_JET_PACK;
}

/*
R: gestion des dégats subit par le joueur
E: 1 TAD joueur 
S: vide
A: Adrien
*/
void degat(int deg,joueur j){
     if(j == NULL){
        fprintf(stderr,"erreur dans la fonction degat() le joueur est NULL\n");
        return;
    }
    j->vie -= deg/j->def;
}


/*
R: fonction d'amelioration des stats du joueur 
E: 1 TAD joueur 
S: vide
A: Adrien
*/
void amelirorer_stat(joueur j,int stat,double val){
    if(j == NULL){
        fprintf(stderr,"erreur dans la fonction améliorer_stats() le joueur est NULL\n");
        return;
    }
    switch (stat)
    {
    case CAP_ATK:j->atk += val;break;
    case CAP_DEF:j->def += val;break;
    case CAP_JET:j->jetpack += val;break;
    case CAP_REG:j->reg += val;break;
    case CAP_VIE:j->vie_max += val;break;
    case CAP_VIT:j->vit += val;break;
    default:break;
    }
}

void niveau_suivant(joueur j){
    if(j->xp <= j->niv*j->seuil){
        j->xp -= j->seuil*j->niv;
        j->niv++;
    }
}




#endif /*_JOUEUR_C_*/