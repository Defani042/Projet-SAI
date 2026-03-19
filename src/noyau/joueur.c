#ifndef _JOUEUR_C_
#define _JOUEUR_C_

#include"noyau/joueur.h"

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
    j->pos = pos;
    j->vit = DEFAULT;

}

void liberer_joueur(joueur j){
    
    if(j != NULL){
        liberer_position(j->pos);
        free(j);
        free(j);
        j = NULL;
    }
}



#endif /*_JOUEUR_C_*/