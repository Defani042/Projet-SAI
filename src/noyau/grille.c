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
        if (g->cellules[i] != NULL) {
            /* Libère chaque cellule dans la ligne si nécessaire */
            for (j = 0; j < g->taille_y; j++)
            {
                if (g->cellules[i][j] != NULL)  /* Vérifie si la cellule existe */
                {
                    if (g->cellules[i][j]->liste != NULL)  /* Vérifie si la liste d'objets existe */
                    {
                        liberer_objet(g->cellules[i][j]->liste);  /* Libère les objets dans la cellule */
                        g->cellules[i][j]->liste = NULL;  /* Mets la liste à NULL après libération */
                    }
                    free(g->cellules[i][j]);  /* Libère la cellule */
                    g->cellules[i][j] = NULL;  /* Mets la cellule à NULL après libération */
                }
            }

            /* Libère la ligne de cellules */
            free(g->cellules[i]);
            g->cellules[i] = NULL;  /* Mets la ligne à NULL après libération */
        }
    }

    /* Libère le tableau de pointeurs de cellules */
    free(g->cellules);
    g->cellules = NULL;  /* Mets le tableau de cellules à NULL après libération */

    /* Libère la structure principale de la grille */
    free(g);
    g = NULL;  /* Mets la grille à NULL après libération pour éviter un accès ultérieur */

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
R: Conversion de la position sur l'axe X en indice de cellule dans la grille
E: 1 double (position sur l'axe X), 1 TAD grille
S: 1 entier (indice de cellule correspondant à la position X, ou -1 si hors des limites)
A: Adrien
*/
int coord_to_cell_x(double pos, grille g)
{
    double centre_x, min_x, max_x;
    int idx;

    /* Calcul dynamique du centre de la grille sur l'axe X */
    centre_x = (g->taille_x * g->cell_size) / 2;  /* Calcul du centre de la grille */
    min_x = -centre_x;  /* Limite inférieure */
    max_x = centre_x;   /* Limite supérieure */

    /* Si la position est hors de la grille, renvoyer -1 */
    if (pos < min_x || pos > max_x) {
        return -1;  /* Hors limites de la grille en X */
    }

    /* Conversion de la position X en indice de cellule */
    idx = (int)((pos + centre_x) / g->cell_size);  /* Décalage pour faire en sorte que la carte aille de 0 à max_x */

    /* Limites de la grille */
    if (idx < 0) idx = 0;  /* Limite inférieure (bord gauche) */
    if (idx >= g->taille_x) idx = g->taille_x - 1;  /* Limite supérieure (bord droit) */

    return idx;
}


/*
R: Conversion de la position sur l'axe Y en indice de cellule dans la grille
E: 1 double (position sur l'axe Y), 1 TAD grille
S: 1 entier (indice de cellule correspondant à la position Y, ou -1 si hors des limites)
A: Adrien
*/
int coord_to_cell_y(double pos, grille g)
{
    double centre_y, min_y, max_y;
    int idx;

    /* Calcul dynamique du centre de la grille sur l'axe Y */
    centre_y = (g->taille_y * g->cell_size) / 2;  /* Calcul du centre de la grille */
    min_y = -centre_y;  /* Limite inférieure */
    max_y = centre_y;   /* Limite supérieure */

    /* Si la position est hors de la grille, renvoyer -1 */
    if (pos < min_y || pos > max_y) {
        return -1;  /* Hors limites de la grille en Y */
    }

    /* Conversion de la position Y en indice de cellule */
    idx = (int)((pos + centre_y) / g->cell_size);  /* Décalage pour faire en sorte que la carte aille de 0 à max_y */

    /* Limites de la grille */
    if (idx < 0) idx = 0;  /* Limite inférieure (bord inférieur) */
    if (idx >= g->taille_y) idx = g->taille_y - 1;  /* Limite supérieure (bord supérieur) */

    return idx;
}

/*
R: On remplit la grille_statique pour les obstacles
E: 1 TAD grille, 1 liste d'objets statiques
S: Rien
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
        /* Calcul des cellules couvertes par l'objet */
        x_start = coord_to_cell_x(o->pos->x, g);  /* Utilisation de coord_to_cell_x */
        y_start = coord_to_cell_y(o->pos->y, g);  /* Utilisation de coord_to_cell_y */
        x_end = coord_to_cell_x(o->pos->x + o->largeur, g);
        y_end = coord_to_cell_y(o->pos->y + o->longueur, g);

        /* Si l'objet est en dehors de la grille (x_start, y_start, x_end, y_end == -1), on l'ignore */
        if (x_start == -1 || y_start == -1 || x_end == -1 || y_end == -1) {
            continue;  /* L'objet est hors limites, on passe au suivant */
        }

        /* S'assurer que les coordonnées restent dans les limites de la grille */
        if (x_start < 0) x_start = 0;
        if (y_start < 0) y_start = 0;
        if (x_end >= g->taille_x) x_end = g->taille_x - 1;
        if (y_end >= g->taille_y) y_end = g->taille_y - 1;

        /* Parcourir toutes les cellules touchées par l'objet et ajouter l'objet dans la grille */
        for (i = x_start; i <= x_end; i++)
        {
            for (j = y_start; j <= y_end; j++)
            {
                copie = copier_objet(o);  /* Copier l'objet pour l'ajouter dans la cellule */
                copie->next = g->cellules[i][j]->liste; 
                g->cellules[i][j]->liste = copie;
            }
        }
    }
}

/*
R: On remplit la grille_dynamique pour les ennemis
E: 1 TAD grille, 1 liste d'ennemis
S: Rien
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
        /* Calcul des cellules couvertes par l'ennemi */
        x_start = coord_to_cell_x(e->obj->pos->x, g);  /* Utilisation de coord_to_cell_x */
        y_start = coord_to_cell_y(e->obj->pos->y, g);  /* Utilisation de coord_to_cell_y */
        x_end = coord_to_cell_x(e->obj->pos->x + e->obj->largeur, g);
        y_end = coord_to_cell_y(e->obj->pos->y + e->obj->longueur, g);

        /* Si l'ennemi est en dehors de la grille (x_start, y_start, x_end, y_end == -1), on l'ignore */
        if (x_start == -1 || y_start == -1 || x_end == -1 || y_end == -1) {
            continue;  /* L'ennemi est hors limites, on passe au suivant */
        }

        /* S'assurer que les coordonnées restent dans les limites de la grille */
        if (x_start < 0) x_start = 0;
        if (y_start < 0) y_start = 0;
        if (x_end >= g->taille_x) x_end = g->taille_x - 1;
        if (y_end >= g->taille_y) y_end = g->taille_y - 1;

        /* Remplir toutes les cellules touchées par l'ennemi */
        for (i = x_start; i <= x_end; i++)
        {
            for (j = y_start; j <= y_end; j++)
            {
                copie = copier_objet(e->obj);  /* Copier l'objet de l'ennemi */
                copie->next = g->cellules[i][j]->liste; 
                g->cellules[i][j]->liste = copie;
            }
        }
    }
}

/*
R: affichage de la grille dans le terminal
E: 1 TAD grilles
S: rien
A: Adrien
*/
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