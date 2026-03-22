#ifndef _OBJET_H_
#define _OBJET_H_

#include <stdio.h>
#include <stdlib.h>

#include "noyau/position.h"


typedef struct s_objet
{
    position pos;
    double cote;
    struct s_objet * next;
}s_objet;

typedef s_objet * objet;


objet creer_objet(position pos,double c);

objet supprimer_objet(objet o,int i);

objet supprimer_objet_ptr(objet liste, objet cible);

void liberer_objet(objet o);

objet concat_objet(objet o1 , objet o2);

objet ajouter_debut(objet liste, objet nouvel_objet);

objet ajouter_fin(objet liste, objet nouvel_objet);

objet obtenir_objet(objet liste, int index);

int taille(objet o);

void afficher_objets(objet liste);

#endif /*_OBJET_H_*/