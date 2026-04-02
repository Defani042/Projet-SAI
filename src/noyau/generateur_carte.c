#ifndef _GENERATEUR_CARTE_C_
#define _GENERATEUR_CARTE_C_

#include "noyau/carte.h"
#include "noyau/generateur_ennemi.h"
#include "moteur/composant3d.h"

carte creer_carte_test()
{
    carte c;
    objet sol;
    objet  obstacle1, obstacle2, obstacle3,obstacle4,mur,mur1,mur2,mur3,plafond;
    position pos_joueur;

    /* Crée une carte vide */
    c = creer_carte_vide();

    /* Initialise le joueur à l'origine avec la macro */
    pos_joueur = creer_position(-5,-5,5);
    c->j = creer_joueur(pos_joueur);
    
    /*Création du sol et du plafond*/
    sol = creer_objet(creer_position(-100,-100,-2),200,200,2);
    c->liste_objets = ajouter_fin(c->liste_objets,sol);

    plafond = creer_objet(creer_position(-100,-100,198),200,200,2);
    c->liste_objets = ajouter_fin(c->liste_objets,plafond);
    
    /* création des mur*/
    mur = creer_objet(creer_position(-100.0, -100, -2), 200, 2, 200);
    c->liste_objets = ajouter_fin(c->liste_objets, mur);

    mur1 = creer_objet(creer_position(100.0, -100, -2), 200, 2, 200);
    c->liste_objets = ajouter_fin(c->liste_objets, mur1);

    mur2 = creer_objet(creer_position(-100.0, 100, -2), 2, 200, 200);
    c->liste_objets = ajouter_fin(c->liste_objets, mur2);

    mur3 = creer_objet(creer_position(-100.0, -100, -2), 2, 200, 200);
    c->liste_objets = ajouter_fin(c->liste_objets, mur3);

    obstacle4 = creer_objet(creer_position(-10.0, -1.0, -10.0), 20.0, 1.0, 20.0);
    c->liste_objets = ajouter_fin(c->liste_objets, obstacle4);

    /* Crée quelques obstacles */
    obstacle1 = creer_objet(creer_position(3.0, 0.0, 2.0), 2.0, 2.0, 2.0);
    obstacle2 = creer_objet(creer_position(-2.0, 0.0, -3.0), 1.5, 1.5, 1.5);
    obstacle3 = creer_objet(creer_position(0.0, 0.0, 5.0), 2.0, 2.0, 2.0);
    

    /* Ajoute les obstacles à la liste */
    c->liste_objets = ajouter_debut(c->liste_objets, obstacle1);
    c->liste_objets = ajouter_debut(c->liste_objets, obstacle2);
    c->liste_objets = ajouter_debut(c->liste_objets, obstacle3);

    return c;
}

void creer_monde(carte c){
    objet ciel1,ciel2,ciel3,ciel4,ciel5,ciel6;

    ciel1= creer_objet(creer_position(-1000,-1000,-1000),2000,2000,1);
    couleur_objet(ciel1, 0.5f, 0.8f, 1.0f);
    c->liste_objets = ajouter_fin(c->liste_objets, ciel1);

    ciel2= creer_objet(creer_position(-1000,-1000,-1000),2000,1,2000);
    couleur_objet(ciel2, 0.5f, 0.8f, 1.0f);
    c->liste_objets = ajouter_fin(c->liste_objets, ciel2);

    ciel3= creer_objet(creer_position(-1000,-1000,-1000),1,2000,2000);
    couleur_objet(ciel3, 0.5f, 0.8f, 1.0f);
    c->liste_objets = ajouter_fin(c->liste_objets, ciel3);

    ciel4= creer_objet(creer_position(-1000,-1000,1000),2000,2000,1);
    couleur_objet(ciel4, 0.5f, 0.8f, 1.0f);
    c->liste_objets = ajouter_fin(c->liste_objets, ciel4);

    ciel5= creer_objet(creer_position(-1000,1000,-1000),1,2000,2000);
    couleur_objet(ciel5, 0.5f, 0.8f, 1.0f);
    c->liste_objets = ajouter_fin(c->liste_objets, ciel5);

    ciel6= creer_objet(creer_position(1000,-1000,-1000),2000,1,2000);
    couleur_objet(ciel6, 0.5f, 0.8f, 1.0f);
    c->liste_objets = ajouter_fin(c->liste_objets, ciel6);

    creer_arbre(c,4,4,0);
    creer_rocher(c,1,-6,0);
    creer_maison(c,-6,1,0);
}

carte creer_carte_jeu(){
    carte c;
    objet sol;

    position pos_joueur;

    /* Crée une carte vide */
    c = creer_carte_vide();

    /* Initialise le joueur à l'origine avec la macro */
    pos_joueur = creer_position(-5,-5,5);
    c->j = creer_joueur(pos_joueur);
    
    /*Création du sol et du plafond*/
    sol = creer_objet(creer_position(-250,-250,-2),500,500,2);
    couleur_objet(sol, 0.0f, 0.3f, 0.0f);

    creer_monde(c);

    init_tab_ennemi();

    c->liste_objets = ajouter_fin(c->liste_objets,sol);

    return c;
}

#endif /*_GENERATEUR_CARTE_C_*/