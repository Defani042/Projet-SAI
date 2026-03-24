#ifndef AFFICHAGE_C
#define AFFICHAGE_C

#include "moteur/controle.h"


/*variables globales*/
int xO = -71;
int yO = -41;
int zO = 2;
float eyeX = 0;
float eyeY = 0;
float eyeZ = 0;
int upX = 0;
int upY = 0;
int upZ = 1;
int l = -16;
int r = 16;
int b = -9;
int top = 9;
int n = 5;
int f = 1000;
int largeur_ecran;
int hauteur_ecran;

/*
R: permet d'initialiser tous les paramètre GLUT
E: rien
S: rien
A: Gaultier
*/
void initialisation(){
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);  
    glutCreateWindow("Projet SAI");
    glutFullScreen();
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutDisplayFunc(affichage);   
    glutIdleFunc(animer);
    glutKeyboardFunc(touche_pressee);
    largeur_ecran = glutGet(GLUT_SCREEN_WIDTH);
    hauteur_ecran = glutGet(GLUT_SCREEN_HEIGHT);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutKeyboardUpFunc(touche_relachee);
    glutWarpPointer(largeur_ecran/2, hauteur_ecran/2);
    glutPassiveMotionFunc(mouvement_souris);
    glutMotionFunc(mouvement_souris);
}

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
R: permet d'actualiser les images
E: rien
S: rien
A: Gaultier
*/
void animer(){
    static clock_t last_time = 0;
    clock_t current_time = clock();
    if (!(current_time - last_time < CLOCKS_PER_SEC / 60)){
        last_time = current_time;
        raffraichir();
        glutPostRedisplay();
    }
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

/*
R: permet d'afficher les images
E: rien
S: rien
A: Gaultier et Adrien
*/
void affichage(){

    /*clock_t debut, fin;
    double temps;
    char buffer[64];

    debut = clock();*/
    /*debut*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* ===================== */
    /*       3D              */
    /* ===================== */


    /*Modif de la visualisation*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(l,r,b,top,n,f);

    /*Init de la matrice de visualisation*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,eyeX + directionX,eyeY + directionY,eyeZ + directionZ,upX,upY,upZ);

    /*Definition des points*/
    glBegin(GL_QUADS); /*GL_POINTS affiche des points et GL_QUADS affiche des rectangles*/

    /*Zone d'affichage*/
    /*Parallelepiped(-40,-40,-5,40,40,5);*/
    afficher_carte(carte_jeu);

    /*printf("ex,ey,ez,xO,y0,z0 : %d,%d,%d,%d,%d,%d\n", eyeX,eyeY,eyeZ,xO,yO,zO);*/

    glEnd();
    /* ===================== */
    /*       UI 2D           */
    /* ===================== */
    /*carte_jeu->j->vie = alea_double(1,carte_jeu->j->vie_max);
    carte_jeu->j->jetpack = alea_double(1,carte_jeu->j->jetpack_max);*/
    glDisable(GL_DEPTH_TEST);
    /* Projection 2D */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, largeur_ecran, hauteur_ecran, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* Dessin UI */
    afficher_interface();

   
    glEnable(GL_DEPTH_TEST); 

    /* Affichage */
    glutSwapBuffers();


    /*Fin*/
    glutSwapBuffers();

    /* Mesure du temps */
    /*fin = clock();
    temps = (double)(fin - debut) / CLOCKS_PER_SEC;
    sprintf(buffer, "%s%s frame calculé en %f sec", MOTEUR, SUCC, temps);
    log_message(buffer);*/
}
#endif /*AFFICHAGE_C*/