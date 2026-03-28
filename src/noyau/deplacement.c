#ifndef _DEPLACEMENT_C_
#define _DEPLACEMENT_C_

#include"noyau/deplacement.h"


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
    move_z = j->dir->z * dx;
    move_z += dz;

    if(move_z > 0.45 && j->jetpack>0){
        utiliser_jetpack(j);
    }
    else{
        if(move_z >0){
            move_z = 0;
        }
    }

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
R: Déplacement d'un ennemi vers le joeur dans la carte avec détection des colision
E: 1 TAD joueur , 1 TAD ennemi(celui qu'on veux déplacer), 1 TAD joueur
S: vide
A: Adrien
*/
void deplacer_ennemi_vers_joueur(carte c, ennemi e, joueur joueur)
{
    float dx, dy, dz;
    float longueur;
    float oldX, oldY, oldZ;
    float vitesse;

    if (c == NULL || e == NULL || e->obj == NULL || joueur == NULL)
    {
        log_message(NOYAU WARN "parametre NULL dans deplacer_ennemi_vers_joueur");
        return;
    }

    vitesse = e->vit;

    /* direction vers le joueur */
    dx = joueur->pos->x - e->obj->pos->x;
    dy = joueur->pos->y - e->obj->pos->y;
    dz = joueur->pos->z - e->obj->pos->z;

    longueur = (float)sqrt(dx*dx + dy*dy + dz*dz);
    if (longueur == 0.0f)
        return;

    dx /= longueur;
    dy /= longueur;
    dz /= longueur;

    /* sauvegarde position */
    oldX = e->obj->pos->x;
    oldY = e->obj->pos->y;
    oldZ = e->obj->pos->z;

    /* ===== Axe X ===== */
    e->obj->pos->x = oldX + dx * vitesse;

    if (detecter_collision_ennemi_objet(c, e) != NULL ||
        detecter_collision_ennemi_ennemi(c, e) != NULL)
    {
        e->obj->pos->x = oldX;
    }

    /* ===== Axe Y ===== */
    e->obj->pos->y = oldY + dy * vitesse;

    if (detecter_collision_ennemi_objet(c, e) != NULL ||
        detecter_collision_ennemi_ennemi(c, e) != NULL)
    {
        e->obj->pos->y = oldY;
    }

    /* ===== Axe Z ===== */
    e->obj->pos->z = oldZ + dz * vitesse;

    if (detecter_collision_ennemi_objet(c, e) != NULL ||
        detecter_collision_ennemi_ennemi(c, e) != NULL)
    {
        e->obj->pos->z = oldZ;
    }
}


/*
R: gestion du déplacement de tous les ennemi
E: 1 TAD carte
S: vide
A: Adrien
*/
void avencer_vague_ennemi(carte c)
{
    ennemi tmp;
    ennemi suivant;
    joueur j;
    double dist;

    if (c == NULL || c->j == NULL)
        return;

    tmp = c->liste_ennemi;
    j = c->j;

    while (tmp != NULL)
    {
        suivant = tmp->next;

        /* verification mort */
        if (mort(tmp))
        {
             log_message(NOYAU SUCC "un ennemie est mort");
            supprimer_ennemi_ptr(c->liste_ennemi, tmp);
        }
        else
        {
            /* déplacement */
            deplacer_ennemi_vers_joueur(c, tmp, j);

            /* recalcul distance après déplacement */
            dist = distance_carre(tmp->obj->pos, j->pos);

            /* zone d'attaque joueur */
            if (dist < j->taille)
            {
                tmp->vie -= j->atk;
            }

            /* collision directe avec joueur */
            if (collision_hitbox(
                    j->pos->x, j->pos->y, j->pos->z,
                    j->largeur, j->hauteur, j->longueur,
                    tmp->obj->pos->x, tmp->obj->pos->y, tmp->obj->pos->z,
                    tmp->obj->largeur, tmp->obj->hauteur, tmp->obj->longueur))
            {
                degat(tmp->degat, j);
            }
        }

        tmp = suivant;
    }
}

#endif /* _COLLISION_C_ */