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
        log_message(NOYAU ERR "Erreur malloc dans creer_carte()");
        fprintf(stderr, "Erreur malloc dans creer_carte()\n");
        exit(EXIT_FAILURE);
    }
    c->liste_objets = liste_objets;
    c->j = j;
    c->liste_ennemi = NULL;
    
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
    log_message(NOYAU SUCC "libération des objets...");
    liberer_objet(c->liste_objets);
    log_message(NOYAU SUCC "libération du joueur...");
    liberer_joueur(c->j);
    log_message(NOYAU SUCC "libération des ennemis...");
    liberer_ennemi(c->liste_ennemi);
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
R: gestion de la colision entre objet et joueur
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
    double x1_min = x1 - w1/2;
    double x1_max = x1 + w1/2;
    double z1_min = z1 - l1/2;
    double z1_max = z1 + l1/2;
    double y1_min = y1 - h1/2;
    double y1_max = y1 + h1/2;

    double x2_min = x2 ;
    double x2_max = x2 + w2;
    double z2_min = z2;
    double z2_max = z2 + l2;
    double y2_min = y2;
    double y2_max = y2 + h2;

    return (
        x1_min < x2_max && x1_max > x2_min &&
        y1_min < y2_max && y1_max > y2_min &&
        z1_min < z2_max && z1_max > z2_min
    );
}

/*
R: gestion de la colision entre deux objet
E: 12 doubles les position et la taille des deux objet
S: 0 si il n'y a pas de colision sinon 1
A: Adrien
*/
int collision_objet(
    double x1, double y1, double z1,
    double w1, double h1, double l1,
    double x2, double y2, double z2,
    double w2, double h2, double l2)
{
    double x1_min = x1;
    double x1_max = x1 + w1;
    double z1_min = z1;
    double z1_max = z1 + l1;
    double y1_min = y1;
    double y1_max = y1 + h1;

    double x2_min = x2 ;
    double x2_max = x2 + w2;
    double z2_min = z2;
    double z2_max = z2 + l2;
    double y2_min = y2;
    double y2_max = y2 + h2;

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
                tmp->pos->x, tmp->pos->y, tmp->pos->z,
                tmp->largeur, tmp->hauteur, tmp->longueur))
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
        collision_objet(tmpo->pos->x,tmpo->pos->y,tmpo->pos->z,
                        tmpo->largeur,tmpo->hauteur,tmpo->longueur,
                        tmpe->pos->x,tmpe->pos->y,tmpe->pos->z,
                        tmpe->largeur,tmpe->hauteur,tmpe->longueur
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
        collision_objet(tmpe1->pos->x,tmpe1->pos->y,tmpe1->pos->z,
                        tmpe1->largeur,tmpe1->hauteur,tmpe1->longueur,
                        tmpe2->pos->x,tmpe2->pos->y,tmpe2->pos->z,
                        tmpe2->largeur,tmpe2->hauteur,tmpe2->longueur
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