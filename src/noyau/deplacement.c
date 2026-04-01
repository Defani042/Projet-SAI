#ifndef _DEPLACEMENT_C_
#define _DEPLACEMENT_C_

#include"noyau/deplacement.h"

int nbkill =0;
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
     if (detecter_collision_joueur(grille_statique,c->j))
        j->pos->x = old_x;

    j->pos->y += move_y * pas;
     if (detecter_collision_joueur(grille_statique,c->j))
        j->pos->y = old_y;

    j->pos->z += move_z * pas;
    if (detecter_collision_joueur(grille_statique,c->j))
        j->pos->z = old_z;
}


/*
R: Déplacement d'un ennemi vers le joueur dans la carte avec détection des collision
E: 1 TAD joueur , 1 TAD ennemi(celui qu'on veux déplacer), 1 TAD joueur
S: vide
A: Adrien
*/
void deplacer_ennemi_vers_joueur(carte c, ennemi e, joueur j)
{
    double old_x, old_y, old_z;
    double move_x, move_y, move_z;
    double dx, dy, dz;
    double longueur;
    double pas;

    /* Vérification des pointeurs */
    if (!c || !e || !e->obj || !e->obj->pos || !j || !j->pos)
        return;

    pas = e->vit;

    /* Sauvegarde position */
    old_x = e->obj->pos->x;
    old_y = e->obj->pos->y;
    old_z = e->obj->pos->z;

    /* Direction vers le joueur */
    dx = j->pos->x - old_x;
    dy = j->pos->y - old_y;
    dz = j->pos->z - old_z;

    longueur = sqrt(dx*dx + dy*dy + dz*dz);
    if (longueur == 0.0)
        return; /* déjà sur le joueur */

    /* Normalisation */
    dx /= longueur;
    dy /= longueur;
    dz /= longueur;

    /* Déplacement avec vitesse */
    move_x = dx * pas;
    move_y = dy * pas;
    move_z = dz * pas;

    /* Appliquer mouvement axe par axe avec collisions */
    e->obj->pos->x += move_x;
    if (detecter_collision_ennemi(grille_statique, e) ||
        detecter_collision_ennemi(grille_dynamique, e)){
            e->obj->pos->x = old_x;
            /*printf("pos bloquer en x\n");*/
        }
        
    e->obj->pos->y += move_y;
    if (detecter_collision_ennemi(grille_statique, e) ||
        detecter_collision_ennemi(grille_dynamique, e)){
        e->obj->pos->y = old_y;
        /*printf("pos bloquer en y\n");*/
    }
       

    e->obj->pos->z += move_z;
    if (detecter_collision_ennemi(grille_statique, e) ||
        detecter_collision_ennemi(grille_dynamique, e)){
            e->obj->pos->z = old_z;
            /*printf("pos bloquer en z\n");*/
        }
       
}

/*
R: test le déplacement 
E: 1 TAD ennemi et 3 double (direction en x,y,z)
S: 1 entier 1 si le déplacement fonctionne sinon 0
A: Adrien
*/
int essayer_deplacement(ennemi e, double dx, double dy, double dz)
{
    double old_x = e->obj->pos->x;
    double old_y = e->obj->pos->y;
    double old_z = e->obj->pos->z;

    e->obj->pos->x += dx;
    e->obj->pos->y += dy;
    e->obj->pos->z += dz;

    if (detecter_collision_ennemi(grille_statique, e) ||
        detecter_collision_ennemi(grille_dynamique, e))
    {
        e->obj->pos->x = old_x;
        e->obj->pos->y = old_y;
        e->obj->pos->z = old_z;
        return 0;
    }

    return 1;
}

/*
R: Déplacement d'un ennemi vers le joueur dans la carte avec détection des collision et contournement des obstacle
E: 1 TAD joueur , 1 TAD ennemi(celui qu'on veux déplacer), 1 TAD joueur
S: vide
A: Adrien
*/
void deplacer_ennemi_vers_joueur2(carte c, ennemi e, joueur j)
{
    double dx, dy, dz;
    double len;
    double pas;

    /* sécurité */
    if (!c || !e || !e->obj || !e->obj->pos || !j || !j->pos)
        return;

    pas = e->vit;

    /* direction vers joueur */
    dx = j->pos->x - e->obj->pos->x;
    dy = j->pos->y - e->obj->pos->y;
    dz = j->pos->z - e->obj->pos->z;

    len = sqrt(dx*dx + dy*dy + dz*dz);
    if (len == 0)
        return;

    dx /= len;
    dy /= len;
    dz /= len;

    /* petit random pour éviter comportement robot */
    dx += alea_double(-0.2, 0.2);
    dy += alea_double(-0.2, 0.2);

    /* renormalisation XY */
    len = sqrt(dx*dx + dy*dy);
    if (len != 0) {
        dx /= len;
        dy /= len;
    }

    /* ===== direction principale ===== */
    if (essayer_deplacement(e, dx*pas, dy*pas, dz*pas)) {
        e->blocage = 0;
        return;
    }

    e->blocage++;

    /* ===== droite ===== */
    if (essayer_deplacement(e, -dy*pas, dx*pas, 0))
        return;

    /* ===== gauche ===== */
    if (essayer_deplacement(e, dy*pas, -dx*pas, 0))
        return;

    /* ===== comportement secours ===== */
    if (e->blocage > 5)
    {
        double rx = alea_double(-1,1);
        double ry = alea_double(-1,1);

        essayer_deplacement(e, rx*pas, ry*pas, 0);
        e->blocage = 0;
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
            j->xp += tmp->xp;
            log_message(NOYAU SUCC "un ennemie est mort");
            nbkill++;
            /*printf("kill == %d\n",nbkill);*/
            c->liste_ennemi = supprimer_ennemi_ptr(c->liste_ennemi, tmp);
        }
        else
        {
            /* déplacement */
            deplacer_ennemi_vers_joueur2(c, tmp, j);

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
                    CENTRER,
                    tmp->obj->pos->x, tmp->obj->pos->y, tmp->obj->pos->z,
                    tmp->obj->largeur, tmp->obj->hauteur, tmp->obj->longueur,
                NO_CENTRER)
            )
            {
                degat(tmp->degat, j);
            }
        }

        tmp = suivant;
    }
}

#endif /* _COLLISION_C_ */