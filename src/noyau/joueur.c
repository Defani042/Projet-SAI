#ifndef _JOUEUR_C_
#define _JOUEUR_C_

#include"noyau/joueur.h"
#include"moteur/controle.h"

/*VAR GLOBALE*/
clock_t dernier_temps_jetpack = 0;
clock_t dernier_temps_degat = 0;

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
    j->niv = 1;
    j->xp = 0;
    j->vie = VIE;
    j->vie_max = VIE;
    j->pos = pos;
    j->vit = DEFAULT;
    j->def = DEFAULT;
    j->seuil = SEUIL;
    j->taille = TAILLE;

    /*hitbox du joueur*/
    j->hauteur = HAUT;
    j->largeur = LARG;
    j->longueur = LONG;

    /*regeneration*/
    j->reg_jetpack = 0.05;
    j->reg_vie = 0.05;
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
    dernier_temps_jetpack = clock();
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
        log_message(NOYAU WARN "Joueur NULL! fonction degat()");
        return;
    }
    dernier_temps_degat = clock();
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
    case CAP_JET:{
        j->jetpack_max += val;
        j->jetpack += val;
        break;
    }
    case CAP_REG:j->reg_vie += val;break;
    case CAP_VIE:{
        j->vie_max += val;
        j->vie += val;
        break;
    }
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
    char buff[64];

    if(j->xp >= j->niv * j->seuil){
        sprintf(buff, "%s%s passage du niveau %d au niveau %d", NOYAU, SUCC, j->niv, j->niv + 1);
        log_message(buff);

        j->niv++;          /* niveau supérieur */
        j->xp = 0;         /* réinitialisation de l'expérience */
        j->seuil *= 2;     /* seuil pour le prochain niveau */
        show_menu_upgrade(); /*affiche le menu d'amélioration*/
    }
}

/*
R: fonction pour replacer le joueur sur la map 
E: 1 TAD joueur 
S: vide
A: Adrien
*/
void reapparition(joueur j){
    if(j->pos->z < -100){
        j->pos->x = -5;
        j->pos->y = -5;
        j->pos->z = 5;
        degat(VOID_DAMAGE,j);
        log_message(NOYAU SUCC "replacement du joueur en (0,0,5)");
        
    }

}

/*
R: regeneration du jetpack
E: 1 TAD joueur 
S: vide
A: Adrien
*/
void regenerer_jetpack(joueur j) {
    clock_t curr_time = clock();
    double durrer = (double)(curr_time - dernier_temps_jetpack) / CLOCKS_PER_SEC;

    if (durrer >= DURRER_JET) {
        /*Ajoute la régénération*/
        j->jetpack += j->reg_jetpack;

        /*Limite à la valeur max*/
        if (j->jetpack > j->jetpack_max) {
            j->jetpack = j->jetpack_max;
        }
    }
}

/*
R: regeneration de la vie 
E: 1 TAD joueur 
S: vide
A: Adrien
*/
void regeneration_vie(joueur j){
    clock_t curr_time = clock();
    double durrer = (double)(curr_time - dernier_temps_degat) / CLOCKS_PER_SEC;
     if (durrer >= DURRER_VIE) {
        /*Ajoute la régénération*/
        j->vie += j->reg_vie;

        /*Limite à la valeur max*/
        if (j->vie > j->vie_max) {
            j->vie = j->vie_max;
        }
    }
}



#endif /*_JOUEUR_C_*/