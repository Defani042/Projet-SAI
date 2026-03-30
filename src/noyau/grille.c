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
    
    /* Remplissage du pointeur pour la grille */
    if ((g = (grille)malloc(sizeof(s_grille))) == NULL)
    {
        fprintf(stderr, "Erreur malloc par la fonction creer_grille()\n");
        log_message(NOYAU ERR "Erreur malloc par la fonction creer_grille()");
        exit(EXIT_FAILURE);
    }
    
    /* Remplissage des champs simples */
    g->taille_x = taille_x;
    g->taille_y = taille_y;
    g->cell_size = cell_size;

    /* Allocation du tableau 2D d'objets */
    if ((g->objets = (objet **)malloc(sizeof(objet *) * taille_x)) == NULL)
    {
        fprintf(stderr, "Erreur malloc par la fonction creer_grille() pour les lignes\n");
        log_message(NOYAU ERR "Erreur malloc pour les lignes dans creer_grille()");
        exit(EXIT_FAILURE);
    }

    /* Allocation des cases du tableau */
    for (i = 0; i < taille_x; i++)
    {
        if ((g->objets[i] = (objet *)malloc(sizeof(objet) * taille_y)) == NULL)
        {
            fprintf(stderr, "Erreur malloc par la fonction creer_grille() pour la colonne [%d]\n", i);
            log_message(NOYAU ERR "Erreur malloc pour la colonne dans creer_grille()");
            exit(EXIT_FAILURE);
        }
        
        /* Initialisation des objets dans chaque cellule */
        for (j = 0; j < taille_y; j++)
        {
            g->objets[i][j] = NULL;  /*Initialisation à NULL (aucun objet dans la cellule au départ)*/
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

    /* Libère les objets dans chaque cellule */
    for (i = 0; i < g->taille_x; i++)
    {
        if (g->objets[i] != NULL)  /*Vérifie que la ligne n'est pas NULL*/ 
        {
            for (j = 0; j < g->taille_y; j++)
            {
                if (g->objets[i][j] != NULL)  /*Vérifie que l'objet existe dans la cellule*/
                {
                    liberer_objet(g->objets[i][j]);  /*Libère l'objet dans la cellule*/ 
                    g->objets[i][j] = NULL;  /* Mets l'objet à NULL après libération*/
                }
            }

            /* Libère la ligne d'objets */
            free(g->objets[i]);
            g->objets[i] = NULL;  /*Mets la ligne à NULL après libération*/
        }
    }

    /* Libère le tableau de pointeurs d'objets */
    free(g->objets);
    g->objets = NULL;  /*Mets le tableau de cellules à NULL après libération*/ 

    /* Libère la structure principale de la grille */
    free(g);
    g = NULL;  /*Mets la grille à NULL après libération pour éviter un accès ultérieur*/ 

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
            liberer_objet(g->objets[i][j]);
            g->objets[i][j] = NULL; /*on vide juste la liste*/
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
        y_end = coord_to_cell_y(o->pos->y + o->hauteur, g);

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
                copie->next = g->objets[i][j]; 
                g->objets[i][j] = copie;
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
        y_end = coord_to_cell_y(e->obj->pos->y + e->obj->hauteur, g);

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
                copie->next = g->objets[i][j]; 
                g->objets[i][j] = copie;
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
            n = taille_objet(g->objets[i][j]);
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

/*
R: affichage de la grille dans les log
E: 1 TAD grilles
S: rien
A: Adrien
*/

void afficher_grille_log(grille g)
{
    int i, j;
    int n;
    char buffer[1024];  /* Buffer temporaire pour stocker chaque ligne à loguer */

    if (!g)
        return;

    /* Affichage des indices des colonnes dans les logs */
    strcpy(buffer, " ");  /* Espace pour les indices de lignes */
    for (i = 0; i < g->taille_x; i++)
    {
        sprintf(buffer + strlen(buffer), "%3d", i);  /* Ajout des numéros de colonnes */
    }
    log_message(buffer);  /* Envoi de la ligne avec les indices de colonnes */

    /* Ligne supérieure avec les séparateurs de colonnes */
    strcpy(buffer, " ");
    for (i = 0; i < g->taille_x; i++)
    {
        strcat(buffer, "---");
    }
    log_message(buffer);  /* Affichage de la ligne de séparation */

    /* Parcours de la grille (axe Y de haut en bas) */
    for (j = g->taille_y - 1; j >= 0; j--)
    {
        /* Numéro de ligne */
        sprintf(buffer, "%2d|", j);
        for (i = 0; i < g->taille_x; i++)
        {
            n = taille_objet(g->objets[i][j]);
            if (n > 0)
                sprintf(buffer + strlen(buffer), "%2d ", n);  /* Affiche le nombre d'objets dans la cellule */
            else
                strcat(buffer, " . ");  /* Affiche un point pour une cellule vide */
        }
        log_message(buffer);  /* Affichage de la ligne avec les objets */
    }

    /* Ligne du bas avec les séparateurs */
    strcpy(buffer, " ");
    for (i = 0; i < g->taille_x; i++)
    {
        strcat(buffer, "---");
    }
    log_message(buffer);  /* Affichage de la ligne de séparation */
}
#endif /*_GRILLE_C_*/