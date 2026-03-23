#ifndef _CARTE_C_
#define _CARTE_C_

#include "noyau/carte.h"

/*
R: création d'un TAD carte
E: 1 TAD objet et 1 TAD joueur 
S: 1 TAD carte
A: Adrien
*/
carte creer_carte(objet liste_objets, joueur j)
{
    carte c;
    if ((c = (carte)malloc(sizeof(s_carte))) == NULL)
    {
        log_message(NOYAU SUCC "Erreur malloc dans creer_carte()");
        fprintf(stderr, "Erreur malloc dans creer_carte()\n");
        exit(EXIT_FAILURE);
    }
    c->liste_objets = liste_objets;
    c->j = j;
    
    log_message(NOYAU SUCC "Carte créé");
    return c;
}


/*
R: libération du TAD carte
E: 1 TAD objet et 1 TAD joueur 
S: 1 TAD carte
A: Adrien
*/
void liberer_carte(carte c)
{
    if (c == NULL)
        return;

    /* libérer la liste d'objets */
    if (c->liste_objets != NULL)
        liberer_objet(c->liste_objets);

    /* libérer le joueur */
    if (c->j != NULL)
        liberer_joueur(c->j);

    free(c);

    log_message(NOYAU SUCC "Carte libéré");
}


/*
R: création d'un TAD carte vide
E: vide
S: 1 TAD carte vide
A: Adrien
*/
carte creer_carte_vide()
{
    return creer_carte(NULL, NULL);
}

/*
R: gestiond de la colision
E: 12 doubles les position et la taille des deux objet
S: 0 si il n'y a pas de colision sinon 1
A: Adrien
*/
int collision_hitbox(
    double x1, double y1, double z1,
    double w1, double h1, double l1,
    double x2, double y2, double z2,
    double w2, double h2, double l2)
{
    return (
        x1 < x2 + w2 &&
        x1 + w1 > x2 &&
        y1 < y2 + h2 &&
        y1 + h1 > y2 &&
        z1 < z2 + l2 &&
        z1 + l1 > z2
    );
}

/*
R: gestion de la colision avec tous les pbjet de la carte
E: 1 TAD carte
S: l'objet en colistion avec le joeur ou NULL si aucune colision
A: Adrien
*/
objet detecter_collision_joueur(carte c)
{
    objet tmp;

    if (c == NULL || c->j == NULL)
        return NULL;

    tmp = c->liste_objets;

    while (tmp != NULL)
    {
        if (collision_hitbox(
                c->j->pos->x, c->j->pos->y, c->j->pos->z,
                c->j->largeur, c->j->hauteur, c->j->longueur,
                tmp->pos->x, tmp->pos->y, tmp->pos->z,
                tmp->largeur, tmp->hauteur, tmp->longueur))
        {
            return tmp;  /* collision trouvée */
        }

        tmp = tmp->next;
    }

    return NULL; /* pas de collision */
}

/*
R: Déplacement d'un joueur dans la carte avec détection des colision
E: 1 TAD joueur et 3 double (les direction sur les axe X,Y et Z)
S: vide
A: Adrien
*/
void deplacer_joueur(carte c, double dirx, double diry, double dirz)
{
    double norme, nx, ny, nz;
    double old_x, old_y, old_z;

    if (c == NULL || c->j == NULL || c->j->pos == NULL)
        return;

    /* calcul de la norme */
    norme = sqrt(dirx*dirx + diry*diry + dirz*dirz);

    /* pas de déplacement */
    if (norme == 0)
        return;

    /* normalisation */
    nx = dirx / norme;
    ny = diry / norme;
    nz = dirz / norme;

    /* sauvegarde ancienne position */
    old_x = c->j->pos->x;
    old_y = c->j->pos->y;
    old_z = c->j->pos->z;

    /* déplacement axe par axe */
    c->j->pos->x += nx * c->j->vit;
    if (detecter_collision_joueur(c) != NULL)
        c->j->pos->x = old_x;

    c->j->pos->y += ny * c->j->vit;
    if (detecter_collision_joueur(c) != NULL)
        c->j->pos->y = old_y;

    c->j->pos->z += nz * c->j->vit;
    if (detecter_collision_joueur(c) != NULL)
        c->j->pos->z = old_z;
}

/*
R: permet de vérifier si la partie est finie
E: 1 TAD carte
S: 0 si la partie est finie sinon 1
A: Adrien
*/
int game_over(carte c){
    return(c->j->vie == 0);
}

#endif /*_CARTE_C_*/