#ifndef _MENU_AMELIORATION_H_
#define _MENU_AMELIORATION_H_

#include "moteur/composant2d.h"
#include "moteur/affichage.h"
#include "config/config.h"

extern char description1[NB_MAX];
extern char description1[NB_MAX];
extern char description1[NB_MAX];

extern int stat_competence1;
extern int stat_competence2;
extern int stat_competence3;

extern int val1;
extern int val2;
extern int val3;

void choix_competence();

void afficher_fenetre_amelioration();

#endif /*_MENU_AMELIORATION_H_*/