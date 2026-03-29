#ifndef _GRILLE_C_
#define _GRILLE_C_

#include "noyau/grille.h"

/*
R: création d'une grille
E: 2 entiers (la taille x et la taille y du tableau) 1 double qui représente la taille de la grille (portion de la carte)
S: 1 TAD grille
A: Adrien
*/
grille creer_grille(int taille_x, int taille_y, double cell_size)
{
    grille g;
    int i, j;
    /*remplissage du pointeur*/
    if ((g = (grille)malloc(sizeof(s_grille))) == NULL)
    {
        fprintf(stderr, "Erreur malloc par la fonction creer_grille()\n");
        log_message(NOYAU ERR "Erreur malloc par la fonction creer_grille()");
        exit(EXIT_FAILURE);
    }
    /*remplissage des champs simple*/
    g->taille_x = taille_x;
    g->taille_y = taille_y;
    g->cell_size = cell_size;

    /*allocution du tableau*/
    if ((g->cellules = (cellule **)malloc(sizeof(cellule *) * taille_x)) == NULL)
    {
        fprintf(stderr, "Erreur malloc par la fonction creer_grille()\n");
        log_message(NOYAU ERR "Erreur malloc par la fonction creer_grille()");
        exit(EXIT_FAILURE);
    }
    /*allocution des case du tableau*/
    for (i = 0; i < taille_x; i++)
    {
        if ((g->cellules[i] = (cellule *)malloc(sizeof(cellule) * taille_y)) == NULL)
        {
            fprintf(stderr, "Erreur malloc par la fonction creer_grille()\n");
            log_message(NOYAU ERR "Erreur malloc par la fonction creer_grille()");
            exit(EXIT_FAILURE);
        }
        for (j = 0; j < taille_y; j++)
        {
            g->cellules[i][j] = (cellule)malloc(sizeof(s_cellule));
            if (!g->cellules[i][j])
            {
                fprintf(stderr, "Erreur malloc pour cellule [%d][%d]\n", i, j);
                log_message(NOYAU ERR "Erreur malloc pour cellule par la fonction creer_grille()");
                exit(EXIT_FAILURE);
            }
            g->cellules[i][j]->liste = NULL;
        }
    }
    log_message(NOYAU SUCC "Grille créée");
    return g;
}

/*
R: Supression de la grille
E: 1 TAD grilles
S: rien
A: Adrien
*/
void detruire_grille(grille g)
{
    int i, j;

    /* Vérifie si la grille est valide */
    if (g == NULL)
    {
        return;
    }

    /* Libère les cellules dans chaque ligne */
    for (i = 0; i < g->taille_x; i++)
    {
        /* Libère chaque cellule dans la ligne si nécessaire */
        for (j = 0; j < g->taille_y; j++)
        {
            /* Si chaque cellule a une ressource à libérer (par exemple liste), libérer ici */
            /* Exemple : free(g->cellules[i][j].liste); */
            liberer_objet(g->cellules[i][j]->liste);
        }

        /* Libère la ligne de cellules */
        free(g->cellules[i]);
    }

    /* Libère le tableau de pointeurs de cellules */
    free(g->cellules);

    /* Libère la structure principale */
    free(g);

    log_message(NOYAU SUCC "Grille libérée.");
}

/*
R: on vide la grille
E: 1 TAD grilles
S: rien
A: Adrien
*/
void vider_grille(grille g)
{
    int i, j;
    for (i = 0; i < g->taille_x; i++)
    {
        for (j = 0; j < g->taille_y; j++)
        {
            g->cellules[i][j]->liste = NULL; /*on vide juste la liste*/
        }
    }
}

/*
R: converti les coordonnes en
E: 1 TAD grilles
S: rien
A: Adrien
*/
int coord_to_cell(double pos, double cell_size, int taille)
{
    int idx = (int)(pos / cell_size);
    if (idx < 0)
        idx = 0;
    if (idx >= taille)
        idx = taille - 1;
    return idx;
}

/*
R: on remplie la grille_statique pour les obstacle
E: 1 TAD grilles
S: rien
A: Adrien
*/
void remplir_grille_statique(grille g, objet liste_objets)
{
    objet o;
    objet copie;
    int x_start, y_start, x_end, y_end;
    int i, j;
    for (o = liste_objets; o != NULL; o = o->next)
    {
        /*je calcul les cellules couvertes par l'objet*/
        x_start = (int)(o->pos->x / g->cell_size);
        y_start = (int)(o->pos->y / g->cell_size);
        x_end = (int)((o->pos->x + o->largeur) / g->cell_size);
        y_end = (int)((o->pos->y + o->longueur) / g->cell_size);

        /*S'assurer qu'on reste dans les limites de la grille*/
        if (x_start < 0)
            x_start = 0;
        if (y_start < 0)
            y_start = 0;
        if (x_end >= g->taille_x)
            x_end = g->taille_x - 1;
        if (y_end >= g->taille_y)
            y_end = g->taille_y - 1;

        /*Parcourir toutes les cellules touchées par l'objet*/
        for (i = x_start; i <= x_end; i++)
        {
            for (j = y_start; j <= y_end; j++)
            {
                /*on ajoute l'objet dans la grille*/
                copie = copier_objet(o); 
                copie->next = g->cellules[i][j]->liste; 
                g->cellules[i][j]->liste = copie;
            }
        }
    }
}

/*
R: on remplie la grille_dynamique pour les obstacle
E: 1 TAD grilles
S: rien
A: Adrien
*/
void remplir_grille_dynamique(grille g, ennemi liste_ennemis)
{
    ennemi e;
    int x_start, y_start, x_end, y_end;
    int i, j;
    objet copie;

    for (e = liste_ennemis; e != NULL; e = e->next)
    {
        /* calcul des cellules couvertes par l'ennemi */
        x_start = (int)(e->obj->pos->x / g->cell_size);
        y_start = (int)(e->obj->pos->y / g->cell_size);
        x_end = (int)((e->obj->pos->x + e->obj->largeur) / g->cell_size);
        y_end = (int)((e->obj->pos->y + e->obj->longueur) / g->cell_size);

        /* s'assurer de rester dans les limites */
        if (x_start < 0)
            x_start = 0;
        if (y_start < 0)
            y_start = 0;
        if (x_end >= g->taille_x)
            x_end = g->taille_x - 1;
        if (y_end >= g->taille_y)
            y_end = g->taille_y - 1;

        /* remplir toutes les cellules touchées par l'ennemi */
        for (i = x_start; i <= x_end; i++)
        {
            for (j = y_start; j <= y_end; j++)
            {
                copie = copier_objet(e->obj); 
                copie->next = g->cellules[i][j]->liste; 
                g->cellules[i][j]->liste = copie;
            }
        }
    }
}

void afficher_grille(grille g)
{
    int i, j;
    int n;
    if (!g)
        return;  /* Affichage des indices des colonnes */
    printf(" "); /* espace pour les indices de lignes */
    for (i = 0; i < g->taille_x; i++)
    {
        printf("%3d", i);
    }
    printf("\n"); /* Ligne supérieure */
    printf(" ");
    for (i = 0; i < g->taille_x; i++)
    {
        printf("---");
    }
    printf("\n");
    /* Parcours de la grille (axe Y de haut en bas) */
    for (j = g->taille_y - 1; j >= 0; j--)
    {
        printf("%2d|", j); /* numéro de ligne */
        for (i = 0; i < g->taille_x; i++)
        {
            n = taille_objet(g->cellules[i][j]->liste);
            if (n > 0)
                printf("%2d ", n);
            else
                printf(" . ");
        }
        printf("\n");
    } /* Ligne du bas */
    printf(" ");
    for (i = 0; i < g->taille_x; i++)
    {
        printf("---");
    }
    printf("\n");
}

#endif /*_GRILLE_C_*/