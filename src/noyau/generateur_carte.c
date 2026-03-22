#ifndef _GENERATEUR_CARTE_C_
#define _GENERATEUR_CARTE_C_

#include "noyau/carte.h"

carte creer_carte_test()
{
    carte c;
    objet sol, obstacle1, obstacle2, obstacle3;
    position pos_joueur;

    /* Crée une carte vide */
    c = creer_carte_vide();

    /* Initialise le joueur à l'origine avec la macro */
    pos_joueur = SET_UP_ORIGINE_POS;
    c->j = creer_joueur(pos_joueur);

    /* Crée le sol */
    sol = creer_objet(creer_position(-10.0, -1.0, -10.0), 20.0, 1.0, 20.0);
    c->liste_objets = ajouter_fin(c->liste_objets, sol);

    /* Crée quelques obstacles */
    obstacle1 = creer_objet(creer_position(3.0, 0.0, 2.0), 2.0, 2.0, 2.0);
    obstacle2 = creer_objet(creer_position(-2.0, 0.0, -3.0), 1.5, 1.5, 1.5);
    obstacle3 = creer_objet(creer_position(0.0, 0.0, 5.0), 2.0, 2.0, 2.0);

    /* Ajoute les obstacles à la liste */
    c->liste_objets = ajouter_fin(c->liste_objets, obstacle1);
    c->liste_objets = ajouter_fin(c->liste_objets, obstacle2);
    c->liste_objets = ajouter_fin(c->liste_objets, obstacle3);

    return c;
}

#endif /*_GENERATEUR_CARTE_C_*/