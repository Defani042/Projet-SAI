#ifndef _ENNELI_H_
#define _ENNELI_H_


#include <stdio.h>
#include <stdlib.h>

#include "noyau/objet.h"

#define VIT_E 0.8
#define VIE_E 20
typedef struct  s_ennemi
{
    objet obj;/*sprite 3D*/
    double vie;
    double degat;
    double vit;
    int xp;
    struct s_ennemi* next;
}s_ennemi;

/*typedef s_ennemi* ennemi;
*/

ennemi creer_ennemi(objet o);

ennemi supprimer_ennemi_ptr(ennemi head,ennemi cible);

void liberer_ennemi(ennemi e);

ennemi ajouter_ennemi(ennemi e1,ennemi e2);

int mort(ennemi e);

int taille_ennemi(ennemi e);

#endif /*_ENNELI_H_*/