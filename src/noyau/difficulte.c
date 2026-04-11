#ifndef _DIFFICULTE_C_
#define _DIFFICULTE_C_

#include "noyau/difficulte.h"

int difficulte = 0;
int dernier_changement = 0; /*le temps écouler depuis le dernier changement de difficulte*/
int nb_ennemi_max = NBMAX_ENNEMI;




/*
R: gestion de la difficulte
E: rien
S: rien
A: Gaultier et Adrien
*/
void gestion_difficulte(){
    int now = glutGet(GLUT_ELAPSED_TIME); /*temps en ms*/ 
    char buff[64];
    if (now - dernier_changement >= 120000) { /*tous les 2 min*/
        difficulte++;
        dernier_changement = now;
        sprintf(buff,"%s%s Difficulté augmentée : %d",NOYAU,SUCC,difficulte);
        log_message(buff);

        popup_texte = "AUGMENTATION DE LA DIFFICULTE"; 
        popup_fin_time = now + 3000; 
        popup_r = 1.0f; 
        popup_g = 1.0f;
        popup_b = 0.0f;
    }
}


#endif /*_DIFFICULTE_C_*/