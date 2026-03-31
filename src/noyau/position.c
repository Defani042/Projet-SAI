#ifndef _POSITION_C_
#define _POSITION_C_

#include "noyau/position.h"

/*
R: création d'une position
E: 3 double les coordonnées
S: 1 TAD position
A: Adrien
*/
position creer_position(double x, double y , double z){
    position p = NULL;
    if ((p = (position)malloc(sizeof(s_position))) == NULL)
	{
        fprintf(stderr,"Erreur malloc par la fonction creer_position()\n");
        log_message(NOYAU ERR "Erreur malloc par la fonction creer_position()");
        exit(EXIT_FAILURE);
    }
    p->x = x;
    p->y = y;
    p->z = z;
    /*log_message(NOYAU SUCC "Position créé");*/
    return p;
}

/*
R: libération d'une position en mémoire
E: 1 TAD position
S: rien
A: Adrien
*/
void liberer_position(position p){
    if(p != NULL){
        free(p);
        p = NULL;
    }
    /*log_message(NOYAU SUCC "Position libéré");*/
}

/*
R: renvoie la distance au carré entre deux position
E: 2 TAD les deux position dans l'espace
S: un double la distance au carré
A: Adrien
*/
double distance_carre(position p1, position p2){
    double dx = p2->x - p1->x;
    double dy = p2->y - p1->y;
    double dz = p2->z - p1->z;
    return dx * dx + dy * dy + dz * dz; 
}

#endif /*_POSITION_C_*/