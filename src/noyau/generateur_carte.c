#ifndef _GENERATEUR_CARTE_C_
#define _GENERATEUR_CARTE_C_

#include "noyau/carte.h"
#include "noyau/generateur_ennemi.h"
#include "moteur/composant3d.h"
#include "config/config.h"
#include "noyau/aleatoire.h"

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

/*
R: creer aléatoire des rochers sur un sol
E: 1 TAD objet (le sol)
S: 1 TAD objet (la liste des rochers)
A: Adrien
*/
objet creer_rocher_aleatoire(objet sol){
    int i;
    double x,y,z;
    objet tmp = NULL;
    
    for (i = 0; i < MAX_ROCHER; i++)
    {
        /* generation aléatoire */
        x = alea_double(sol->pos->x,sol->pos->x + sol->largeur);
        y = alea_double(sol->pos->y,sol->pos->y + sol->hauteur);
        z = sol->pos->z+sol->longueur;

        tmp = ajouter_debut(tmp,creer_rocher(x,y,z));      
    }
    return tmp;
}

/*
R: creer aléatoire des arbres sur un sol
E: 1 TAD objet (le sol)
S: 1 TAD objet (la liste des arbres)
A: Adrien
*/
objet creer_arbre_aleatoire(objet sol){
    int i;
    double x,y,z;
    objet tmp = NULL;
    
    for (i = 0; i < MAX_ARBRE; i++)
    {
        /* generation aléatoire */
        x = alea_double(sol->pos->x,sol->pos->x + sol->largeur);
        y = alea_double(sol->pos->y,sol->pos->y + sol->hauteur);
        z = sol->pos->z+sol->longueur;

        tmp = ajouter_debut(tmp,creer_arbre(x,y,z));      
    }
    return tmp;
}

/*
R: creer aléatoire des maison sur un sol
E: 1 TAD objet (le sol)
S: 1 TAD objet (la liste des maisons)
A: Adrien
*/
objet creer_maison_aleatoire(objet sol){
    int i;
    double x,y,z;
    objet tmp = NULL;
    
    for (i = 0; i < MAX_MAISON; i++)
    {
        /* generation aléatoire */
        x = alea_double(sol->pos->x,sol->pos->x + sol->largeur);
        y = alea_double(sol->pos->y,sol->pos->y + sol->hauteur);
        z = sol->pos->z+sol->longueur;


        tmp = ajouter_debut(tmp,creer_maison(x,y,z));      
    }
    return tmp;
}


/*
R: creer aléatoire du sol
E: 1 TAD carte
S: rien
A: Adrien
*/
void creer_sol_aleatoire(carte c){
    int i;
    objet plateforme = NULL;
    objet rochers,village,foret;
    double x,y,z;
    for (i = 0; i <MAX_PLATEFORME; i++) {
        x = alea_double(-1000, 1000);
        y = alea_double(-1000, 1000);
        z = alea_double(0, 800);

        plateforme = creer_objet(creer_position(x, y, z),100, 100, 10);
        couleur_objet(plateforme, 0.0f, 0.3f, 0.0f);
        foret = creer_arbre_aleatoire(plateforme);
        rochers = creer_rocher_aleatoire(plateforme);
        village = creer_maison_aleatoire(plateforme);
        /*ajoutons les objet à la scene*/
        c->liste_objets = concat_objet(c->liste_objets, village);
        c->liste_objets = concat_objet(c->liste_objets, rochers);
        c->liste_objets = concat_objet(c->liste_objets, foret);
        c->liste_objets = concat_objet(c->liste_objets,plateforme);
    }

}

/*
R: creer le monde du jeu
E: 1 TAD carte
S: rien
A: Adrien
*/
void creer_monde(carte c){
    objet ciel1,ciel2,ciel3,ciel4,ciel5,ciel6;
    int i, x, y;
    objet mai,roc,arb;

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
    creer_sol_aleatoire(c);

    /* Générer des objets aléatoirement */
    for(i = 0; i < 20; i++){
        /* Générer x dans [-250, -11] ou [11, 250] */
        if(alea_int(0, 1) == 0){
            x = alea_int(-250, -11);
        } else {
            x = alea_int(11, 250);
        }
        /* Générer y dans [-250, -11] ou [11, 250] */
        if(alea_int(0, 1) == 0){
            y = alea_int(-250, -11);
        } else {
            y = alea_int(11, 250);
        }
        arb = creer_arbre(x, y, 0);
        c->liste_objets = ajouter_fin(c->liste_objets, arb);
    }

    for(i = 0; i < 20; i++){
        if(alea_int(0, 1) == 0){
            x = alea_int(-250, -11);
        } else {
            x = alea_int(11, 250);
        }
        if(alea_int(0, 1) == 0){
            y = alea_int(-250, -11);
        } else {
            y = alea_int(11, 250);
        }
        roc = creer_rocher(x, y, 0);
        c->liste_objets = ajouter_fin(c->liste_objets, roc);
    }

    for(i = 0; i < 20; i++){
        if(alea_int(0, 1) == 0){
            x = alea_int(-250, -11);
        } else {
            x = alea_int(11, 250);
        }
        if(alea_int(0, 1) == 0){
            y = alea_int(-250, -11);
        } else {
            y = alea_int(11, 250);
        }
        mai = creer_maison(x, y, 0);
        c->liste_objets = ajouter_fin(c->liste_objets, mai);
    }
}
/*
E: rien
S: carte
A: Adrien
*/
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