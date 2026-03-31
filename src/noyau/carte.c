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
    log_message(NOYAU SUCC "Les objets de la carte sont libres");
    log_message(NOYAU SUCC "libération du joueur...");
    liberer_joueur(c->j);
    log_message(NOYAU SUCC "Le Joueur de la carte est libre");
    log_message(NOYAU SUCC "libération des ennemis...");
    liberer_ennemi(c->liste_ennemi);
    log_message(NOYAU SUCC "Les ennemis de la carte sont libres");
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