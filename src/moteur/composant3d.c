#ifndef _COMPOSANT3D_C_
#define _COMPOSANT3D_C_

#include "moteur/composant3d.h"

int nb_obj = 0;
float angle_soleil = M_PI / 2.0f;

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
R: permet de dessiner une sphère
E: les coordonnées et le rayon de la sphère
S: rien
A: Gaultier
*/
void sphere(float x, float y, float z, float radius, float r, float g, float b) {
     glColor3f(r, g, b);
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(radius, 20, 20);
    glPopMatrix();
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

    glColor3f(o->r, o->g, o->b);

    /* Face avant - rouge */
    glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);

    /* Face arrière - vert */
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);

    /* Face gauche - bleu */
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x1, y2, z1);

    /* Face droite - jaune */
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z1);

    /* Face bas - cyan */
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x1, y1, z2);

    /* Face haut - magenta */
    
    glVertex3f(x1, y2, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);

    glEnd();
    glPopMatrix();
}

void afficher_ennemie(ennemi e){
    float x1, y1, z1, x2, y2, z2;
    objet o = e->obj;

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

    glColor3f(1.0f, 0.1f, 0.0f);

    /* Face avant - rouge */
    glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);

    /* Face arrière - vert */
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);

    /* Face gauche - bleu */
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x1, y2, z1);

    /* Face droite - jaune */
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z1);

    /* Face bas - cyan */
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x1, y1, z2);

    /* Face haut - magenta */
    glVertex3f(x1, y2, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);

    glEnd();
    glPopMatrix();
    /*avant les fonction ddu G*/
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
    ennemi e;
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
     /* parcours tous les ennemi */
    e = c->liste_ennemi;
    while (e != NULL)
    {
        /* affiche seulement si visible par le joueur */
        if (objet_visible(j, e->obj)) {
            afficher_ennemie(e);
            nb_obj++;
        }
        e = e->next;
    }
    
}


/*
R: affiche un cercle en 3D
E: carte c
S: rien
A: Adrien
*/
void afficher_cercle3D(position c, float radius)
{   
    int i;
    float angle,x,y,z;
    int segments = 100; /*nombre de segment du cercle*/
    glBegin(GL_LINE_LOOP);

    for(i = 0; i < segments; i++)
    {
        angle = 2.0f * M_PI * i / segments;

        x = c->x + radius * cos(angle);
        y = c->y + radius * sin(angle);
        z = c->z; /*parralléle au plan du point */

        glVertex3f(x, y, z);
    }

    glEnd();
}

/*
R: creer un arbre
E: 3 double (x,y et z)
S: 1 TAD objet (l'arbre)
A: Adrien et Gaultier
*/
objet creer_arbre(int x, int y, int z){
    objet arbre = NULL;
    objet tronc;
    objet feuillage;

    tronc = creer_objet(creer_position(x,y,z),2,2,5);
    couleur_objet(tronc, 0.345f, 0.160f, 0.0f);
    arbre = ajouter_fin(arbre, tronc);

    feuillage = creer_objet(creer_position(x-2,y-2,z+5),6,6,6);
    couleur_objet(feuillage, 0.153f, 0.227f, 0.0f);
    arbre = ajouter_fin(arbre, feuillage);

    return arbre;
}

/*
R: creer un rocher
E: 3 double (x,y et z)
S: 1 TAD objet (rocher)
A: Adrien et Gaultier
*/
objet creer_rocher(int x, int y, int z){
    objet rocher = NULL;
    objet base;
    objet couche1;

    base = creer_objet(creer_position(x,y,z),4,5,2);
    couleur_objet(base, 0.313f, 0.313f, 0.313f);
    rocher = ajouter_fin(rocher, base);

    couche1 = creer_objet(creer_position(x+1,y+2,z+2),2,3,1);
    couleur_objet(couche1, 0.313f, 0.313f, 0.313f);
    rocher = ajouter_fin(rocher, couche1);

    return rocher;
}

/*
R: creer une maison
E: 3 double (x,y et z)
S: 1 TAD objet (maison)
A: Adrien et Gaultier
*/
objet creer_maison(int x, int y, int z){
    objet maison = NULL;
    objet base;
    objet toit1,toit2,toit3;

    base = creer_objet(creer_position(x,y,z),4,4,4);
    couleur_objet(base, 0.8f, 0.5f, 0.3f);
    maison = ajouter_fin(maison, base);

    toit1 = creer_objet(creer_position(x-1,y-1,z+4),6,6,1);
    couleur_objet(toit1, 0.8f, 0.1f, 0.1f);
    maison = ajouter_fin(maison, toit1);

    toit2 = creer_objet(creer_position(x,y,z+5),4,4,1);
    couleur_objet(toit2, 0.8f, 0.1f, 0.1f);
    maison = ajouter_fin(maison, toit2);

    toit3 = creer_objet(creer_position(x+1,y+1,z+6),2,2,1);
    couleur_objet(toit3, 0.8f, 0.1f, 0.1f);
    maison = ajouter_fin(maison, toit3);

    return maison;

}
/*
R: affiche la hitbox du joueur
E: joueur j
S: rien
A: Adrien
*/

void afficher_hitbox_joueur(joueur j){
    double xmax,xmin,ymax,ymin,zmax,zmin;
    /*couleur position de la hit box du joeuur*/
    xmax = j->pos->x + j->largeur/2;
    xmin = j->pos->x - j->largeur/2;
    ymax = j->pos->y + j->hauteur/2;
    ymin = j->pos->y - j->hauteur/2;
    zmax = j->pos->z + j->longueur/2;
    zmin = j->pos->z - j->longueur/2;

    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0); /*couleur rouge*/
    /*Arêtes face arrière*/
    glVertex3d(xmin, ymin, zmin); glVertex3d(xmax, ymin, zmin);
    glVertex3d(xmax, ymin, zmin); glVertex3d(xmax, ymax, zmin);
    glVertex3d(xmax, ymax, zmin); glVertex3d(xmin, ymax, zmin);
    glVertex3d(xmin, ymax, zmin); glVertex3d(xmin, ymin, zmin);

    /*Arêtes face avant*/
    glVertex3d(xmin, ymin, zmax); glVertex3d(xmax, ymin, zmax);
    glVertex3d(xmax, ymin, zmax); glVertex3d(xmax, ymax, zmax);
    glVertex3d(xmax, ymax, zmax); glVertex3d(xmin, ymax, zmax);
    glVertex3d(xmin, ymax, zmax); glVertex3d(xmin, ymin, zmax);

    /*Arêtes verticales*/ 
    glVertex3d(xmin, ymin, zmin); glVertex3d(xmin, ymin, zmax);
    glVertex3d(xmax, ymin, zmin); glVertex3d(xmax, ymin, zmax);
    glVertex3d(xmax, ymax, zmin); glVertex3d(xmax, ymax, zmax);
    glVertex3d(xmin, ymax, zmin); glVertex3d(xmin, ymax, zmax);
    
    glEnd();    
}


/*
R: affiche tous les objets 3d
E: rien
S: rien
A: Adrien
*/
void afficher3d(){
    float soleil_x = 950.0 * cos(angle_soleil);
    float soleil_y = 950.0 * sin(angle_soleil);
    joueur j = carte_jeu->j;
    afficher_carte(carte_jeu);
    afficher_cercle3D(j->pos,j->taille);
    sphere(soleil_x, 0, soleil_y, 50.0, 0.7f, 0.7f, 0);
    sphere(-soleil_x, 0, -soleil_y, 50.0, 0.9f, 0.9f, 0.6f);

    if(show_menu_debug){
        afficher_hitbox_joueur(carte_jeu->j);
    }
}



#endif /*_COMPOSANT3D_C_*/