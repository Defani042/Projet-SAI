#ifndef _COLLISION_C_
#define _COLLISION_C_

#include "noyau/collision.h"
/*
R: gestion de la colision entre objet et joueur
E: 12 doubles les position et la taille des deux objet 2 entier pour savoir si l'objet est centrer(1 centrer sinon 0)
S: 0 si il n'y a pas de colision sinon 1
A: Adrien
*/
int collision_hitbox(
    double x1, double y1, double z1,
    double w1, double h1, double l1,
    int centered1,

    double x2, double y2, double z2,
    double w2, double h2, double l2,
    int centered2)
{
    double x1_min, x1_max;
    double y1_min, y1_max;
    double z1_min, z1_max;

    double x2_min, x2_max;
    double y2_min, y2_max;
    double z2_min, z2_max;

    /* Objet 1 */
    if (centered1) {
        x1_min = x1 - w1 / 2;
        x1_max = x1 + w1 / 2;
        y1_min = y1 - h1 / 2;
        y1_max = y1 + h1 / 2;
        z1_min = z1 - l1 / 2;
        z1_max = z1 + l1 / 2;
    } else {
        x1_min = x1;
        x1_max = x1 + w1;
        y1_min = y1;
        y1_max = y1 + h1;
        z1_min = z1;
        z1_max = z1 + l1;
    }

    /* Objet 2 */
    if (centered2) {
        x2_min = x2 - w2 / 2;
        x2_max = x2 + w2 / 2;
        y2_min = y2 - h2 / 2;
        y2_max = y2 + h2 / 2;
        z2_min = z2 - l2 / 2;
        z2_max = z2 + l2 / 2;
    } else {
        x2_min = x2;
        x2_max = x2 + w2;
        y2_min = y2;
        y2_max = y2 + h2;
        z2_min = z2;
        z2_max = z2 + l2;
    }

    return (
        x1_min < x2_max && x1_max > x2_min &&
        y1_min < y2_max && y1_max > y2_min &&
        z1_min < z2_max && z1_max > z2_min
    );
}
/* 
R: gestion de la colision generique 
E: 1 TAD grille ,6 doubles(coordonnés(x,y,z) et dimension(longeur,largeur,hauteur)) 
S: retourne l'objet colisionner ou NULL A: Adrien 
*/
objet detecter_collision_generique(grille g, double px, double py, double pz, double w, double h, double l, int centered)
{
    int i, j;
    int x_start, x_end, y_start, y_end;
    objet o;
    if (!g)
        return NULL; /* Calcul des cellules couvertes par la hitbox */
    x_start = coord_to_cell_x(centered ? px - w / 2 : px,g);
    x_end = coord_to_cell_x(centered ? px + w / 2 : px + w,g);
    y_start = coord_to_cell_y(centered ? py - h / 2 : py, g);
    y_end = coord_to_cell_y(centered ? py + h / 2 : py + h,g);

    /*on ne gère pas les objet hors de la map*/
    if(x_end == -1 || x_start == -1 || y_end== -1 || y_start ==-1)return NULL;
  

    for (i = x_start; i <= x_end; i++)
    {
        for (j = y_start; j <= y_end; j++)
        {
            o = g->objets[i][j];
            while (o != NULL)
            {
                if (collision_hitbox(px, py, pz, w, h, l, centered, o->pos->x, o->pos->y, o->pos->z, o->largeur, o->hauteur, o->longueur, NO_CENTRER))
                    return o;
                o = o->next;
            }
        }
    }
    return NULL;
} 

/* 
R: gestion de la colision du joueur 
E: 1 TAD grille ,1 TAD joueur 
S: retourne l'objet colisionner ou NULL 
A: Adrien 
*/
objet detecter_collision_joueur(grille g, joueur j)
{
    if (!j)
        return NULL; /* joueur est centré */
    return detecter_collision_generique(g, j->pos->x, j->pos->y, j->pos->z, j->largeur, j->hauteur, j->longueur, 1);
} 
/* 
R: gestion de la colision des ennemie 
E: 1 TAD grille ,1 TAD ennemie 
S: retourne l'objet colisionner ou NULL 
A: Adrien 
*/
objet detecter_collision_ennemi(grille g, ennemi e)
{
    if (!e || !e->obj)
        return NULL;  /* pour chaque objet de l’ennemi */
    return detecter_collision_generique(g, e->obj->pos->x, e->obj->pos->y, e->obj->pos->z, e->obj->largeur, e->obj->hauteur, e->obj->longueur, 0); /* objets non centrés */
}
#endif /* _COLLISION_C_ */