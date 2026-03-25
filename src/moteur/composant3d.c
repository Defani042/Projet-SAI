#ifndef _COMPOSANT3D_C_
#define _COMPOSANT3D_C_

#include "moteur/composant3d.h"

int nb_obj = 0;

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
    
    glBegin(GL_QUADS);
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
    glEnd();
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

    glPushMatrix();

    /* translation de x,y,z de l'objet vers l'origine  */
    glTranslatef(o->pos->x, o->pos->y, o->pos->z);

    /* rotation */
    glRotatef(o->rot->x, 1, 0, 0);
    glRotatef(o->rot->y, 0, 1, 0);
    glRotatef(o->rot->z, 0, 0, 1);

    /* on dessine à l'origine  (0,0,0) */
    x1 = 0;
    y1 = 0;
    z1 = 0;

    x2 = (float)o->largeur;
    y2 = (float)o->hauteur;
    z2 = (float)o->longueur;

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
    glPopMatrix();
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
    nb_obj = 0;

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
            nb_obj++;
        }
        o = o->next;
    }
}

/*
R: affiche tous les objets 3d
E: carte c
S: rien
A: Adrien
*/
void afficher3d(){
    afficher_carte(carte_jeu);
}

#endif /*_COMPOSANT3D_C_*/