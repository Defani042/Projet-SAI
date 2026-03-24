#ifndef _COMPOSANT3D_C_
#define _COMPOSANT3D_C_

#include "moteur/composant3d.h"


/*
R: permet de dessiner un parallepipede
E: les coordonnées du parralepipède
S: rien
A: Gaultier
*/
void Parallelepiped(float x, float y, float z, float dx, float dy, float dz) {
    float hx = dx / 2.0f;
    float hy = dy / 2.0f;
    float hz = dz / 2.0f;
    
    /*Face avant (z +)*/
    glVertex3f(x - hx, y - hy, z + hz);
    glVertex3f(x + hx, y - hy, z + hz);
    glVertex3f(x + hx, y + hy, z + hz);
    glVertex3f(x - hx, y + hy, z + hz);

    /*Face arrière (z -)*/
    glVertex3f(x - hx, y - hy, z - hz);
    glVertex3f(x - hx, y + hy, z - hz);
    glVertex3f(x + hx, y + hy, z - hz);
    glVertex3f(x + hx, y - hy, z - hz);

    /*Face gauche (x -)*/
    glVertex3f(x - hx, y - hy, z - hz);
    glVertex3f(x - hx, y - hy, z + hz);
    glVertex3f(x - hx, y + hy, z + hz);
    glVertex3f(x - hx, y + hy, z - hz);

    /*Face droite (x +)*/
    glVertex3f(x + hx, y - hy, z - hz);
    glVertex3f(x + hx, y + hy, z - hz);
    glVertex3f(x + hx, y + hy, z + hz);
    glVertex3f(x + hx, y - hy, z + hz);

    /*Face haut (y +)*/
    glVertex3f(x - hx, y + hy, z - hz);
    glVertex3f(x - hx, y + hy, z + hz);
    glVertex3f(x + hx, y + hy, z + hz);
    glVertex3f(x + hx, y + hy, z - hz);

    /*Face bas (y -)*/
    glVertex3f(x - hx, y - hy, z - hz);
    glVertex3f(x + hx, y - hy, z - hz);
    glVertex3f(x + hx, y - hy, z + hz);
    glVertex3f(x - hx, y - hy, z + hz);
}

/*
R: permet d'aficher l'objet dans opengl
E: 1 TAD objet
S: rien
A: Adrien
*/
void afficher_objet_couleur(objet o)
{
    float x1, y1, z1, x2, y2, z2;

    /* sécurité */
    if (o == NULL || o->pos == NULL)
        return;

    x1 = (float)o->pos->x;
    y1 = (float)o->pos->y;
    z1 = (float)o->pos->z;

    x2 = x1 + (float)o->largeur;
    y2 = y1 + (float)o->hauteur;
    z2 = z1 + (float)o->longueur;

    glBegin(GL_QUADS);

    /* Face avant - rouge */
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);

    /* Face arrière - vert */
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);

    /* Face gauche - bleu */
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x1, y2, z1);

    /* Face droite - jaune */
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z1);

    /* Face bas - cyan */
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x1, y1, z2);

    /* Face haut - magenta */
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(x1, y2, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);

    glEnd();
}

/*
R: affiche tous les objets de la carte dans OpenGL
E: carte c
S: rien
A: Adrien
*/
void afficher_carte(carte c) {
    objet o;
    joueur j;

    /* sécurité : carte et joueur */
    if (c == NULL)
        return;
    j = c->j;
    if (j == NULL)
        return;

    /* parcours tous les objets */
    o = c->liste_objets;
    while (o != NULL) {
        /* affiche seulement si visible par le joueur */
        if (objet_visible(j, o)) {
            afficher_objet_couleur(o);
        }
        o = o->next;
    }
}

void afficher3d(){
    afficher_carte(carte_jeu);
}

#endif /*_COMPOSANT3D_C_*/