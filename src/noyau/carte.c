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
    char col[128];

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
            sprintf(col,"%s%s collison détetecter en (%f,%f,%f)" ,NOYAU,SUCC,c->j->pos->x,c->j->pos->y,c->j->pos->z);
            log_message(col);
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
void deplacer_joueur(carte c, double dx, double dy, double dz)
{
    joueur j;
    double old_x, old_y, old_z;
    double pas;

    double right_x;
    double right_y; 

    double move_x = 0;
    double move_y = 0;
    double move_z = 0;

    if (!c || !c->j || !c->j->pos)
        return;

    j = c->j;

    pas = j->vit;

    old_x = j->pos->x;
    old_y = j->pos->y;
    old_z = j->pos->z;

    /* Avancer / reculer (dx) */
    move_x += j->dir->x * dx;
    move_y += j->dir->y * dx;


    /* Strafe gauche / droite (dy) */
    right_x = -j->dir->y;
    right_y = j->dir->x;

    move_x += right_x * dy;
    move_y += right_y * dy;

    /* Vertical (dz) */
    move_z = dz;

    /* Application avec collisions */
    j->pos->x += move_x * pas;
    if (detecter_collision_joueur(c))
        j->pos->x = old_x;

    j->pos->y += move_y * pas;
    if (detecter_collision_joueur(c))
        j->pos->y = old_y;

    j->pos->z += move_z * pas;
    if (detecter_collision_joueur(c))
        j->pos->z = old_z;
}
/*
R: permet de vérifier si la partie est finie
E: 1 TAD carte
S: 1 si la partie est finie sinon 0
A: Adrien
*/
int game_over(carte c){
    return(c->j->vie == 0);
}

/*
R: détermine si l'objet est visible par le joueur 
E: 1 TAD joueur et un TAD objet
S: 0 si l'objet est invisible est finie sinon 1
A: Adrien
*/
int objet_visible(joueur j, objet o)
{
    int ix, iy, iz;
    double dx, dy, dz, dist2, dot;
    double x0, y0, z0, w, h, l;
    double coin[3];

    if (j == NULL || o == NULL || j->pos == NULL || o->pos == NULL)
        return 0;

    x0 = o->pos->x; y0 = o->pos->y; z0 = o->pos->z;
    w  = o->largeur; h = o->hauteur; l = o->longueur;

    for (ix = 0; ix <= 1; ix++) { /*pour tous les point qui on x = xmin et x =xmax*/
        coin[0] = x0 + ix * w;
        for (iy = 0; iy <= 1; iy++) { /*pour tous les point qui on y = ymin et  y=ymax*/
            coin[1] = y0 + iy * h;
            for (iz = 0; iz <= 1; iz++) { /*pour tous les point qui on z = zmin et  y=zmax*/
                coin[2] = z0 + iz * l;

                dx = coin[0] - j->pos->x;
                dy = coin[1] - j->pos->y;
                dz = coin[2] - j->pos->z;

                dist2 = dx*dx + dy*dy + dz*dz;
                if (dist2 <= DIST_REND*DIST_REND) {
                    dot = dx*j->dir->x + dy*j->dir->y + dz*j->dir->z;
                    if (dot > 0)
                        return 1;  /* au moins un coin visible */
                }
            }
        }
    }

    return 0; /* aucun coin visible */
}

#endif /*_CARTE_C_*/