#ifndef _POSITION_C_
#define _POSITION_C_

#include "noyau/position.h"

position creer_position(double x, double y , double z){
    position p = NULL;
    if ((p = (position)malloc(sizeof(s_position))) == NULL)
	{
        fprintf(stderr,"Erreur malloc par la fonction creer_position()\n");
        exit(EXIT_FAILURE);
    }
    p->x = x;
    p->y = y;
    p->z = z;
    return p;
}
void liberer_position(position p){
    if(p != NULL){
        free(p);
        p = NULL;
    }

}

#endif /*_POSITION_C_*/