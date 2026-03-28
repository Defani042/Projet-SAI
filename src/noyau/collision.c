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
R: gestion de la colision avec tous les objet de la carte
E: 1 TAD carte
S: l'objet en colistion avec le joueur ou NULL si aucune colision
A: Adrien
*/
objet detecter_collision_joueur(carte c)
{
    objet tmp;
    /*char col[128];*/

    if (c == NULL || c->j == NULL)
        return NULL;

    tmp = c->liste_objets;

    while (tmp != NULL)
    {
        if (collision_hitbox(
                c->j->pos->x, c->j->pos->y, c->j->pos->z,
                c->j->largeur, c->j->hauteur, c->j->longueur,
                CENTRER,
                tmp->pos->x, tmp->pos->y, tmp->pos->z,
                tmp->largeur, tmp->hauteur, tmp->longueur,
                NO_CENTRER
            ))
        {
            /*sprintf(col,"%s%s collison détetecter en (%f,%f,%f)" ,NOYAU,SUCC,c->j->pos->x,c->j->pos->y,c->j->pos->z);
            log_message(col);*/
            return tmp;  /* collision trouvée */
        }

        tmp = tmp->next;
    }

    return NULL; /* pas de collision */
}

/*
R: gestion de la colision avec tous les objet et les ennemie de la carte
E: 1 TAD carte et 1 TAD ennemi
S: l'objet en colistion avec le joueur ou NULL si aucune colision
A: Adrien
*/
objet detecter_collision_ennemi_objet(carte c,ennemi e)
{
     /*char col[128];*/
    objet tmpo = c->liste_objets;
    objet tmpe = e->obj;

    if (c == NULL || e == NULL || e->obj == NULL){
        log_message(NOYAU WARN "un des paramètre de detecter_collision_ennemi_objet() est NULL");
        return NULL;
    }

    while (tmpo!=NULL)
    {
        if (
        collision_hitbox(tmpo->pos->x,tmpo->pos->y,tmpo->pos->z,
                        tmpo->largeur,tmpo->hauteur,tmpo->longueur,
                        NO_CENTRER,
                        tmpe->pos->x,tmpe->pos->y,tmpe->pos->z,
                        tmpe->largeur,tmpe->hauteur,tmpe->longueur
                        ,NO_CENTRER
        ))
        {
            /*sprintf(col,"%s%s collison détetecter en (%f,%f,%f)" ,NOYAU,SUCC,c->j->pos->x,c->j->pos->y,c->j->pos->z);
            log_message(col);*/
            return tmpo;
        }
        tmpo = tmpo->next;/*passage à next*/

    }
    return NULL; /* pas de collision */
    
}


/*
R: gestion de la colision avec tous les ennemi
E: 1 TAD carte et 1 TAD ennemi
S: l'objet en colistion avec le joueur ou NULL si aucune colision
A: Adrien
*/
objet detecter_collision_ennemi_ennemi(carte c,ennemi e)
{
    /*char col[128];*/
    ennemi liste = c->liste_ennemi;
    objet tmpe1;
    objet tmpe2 = e->obj;

    if (c == NULL || e == NULL || e->obj == NULL){
        log_message(NOYAU WARN "un des paramètre de detecter_collision_ennemi_ennemi() est NULL");
        return NULL;
    }
        
    while (liste!=NULL)
    {
        /*objet de l'ennemie courrant*/
        tmpe1 = liste->obj;
        if (
       collision_hitbox(tmpe1->pos->x,tmpe1->pos->y,tmpe1->pos->z,
                        tmpe1->largeur,tmpe1->hauteur,tmpe1->longueur,
                        NO_CENTRER,
                        tmpe2->pos->x,tmpe2->pos->y,tmpe2->pos->z,
                        tmpe2->largeur,tmpe2->hauteur,tmpe2->longueur,
                        NO_CENTRER
        ))
        {
            /*sprintf(col,"%s%s collison détetecter en (%f,%f,%f)" ,NOYAU,SUCC,c->j->pos->x,c->j->pos->y,c->j->pos->z);
            log_message(col);*/
            return tmpe1;
        }
        liste = liste->next;/*passage à next*/

    }
    return NULL; /* pas de collision */
    
}




#endif /* _COLLISION_C_ */