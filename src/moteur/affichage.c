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
int n = 15;
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

    /*Parallelepiped(-40,-40,-5,40,40,5);*/
    afficher3d();

    /*printf("ex,ey,ez,xO,y0,z0 : %d,%d,%d,%d,%d,%d\n", eyeX,eyeY,eyeZ,xO,yO,zO);*/

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
    /*application de la graviter*/
    bas();
    regenerer_jetpack(carte_jeu->j);

    /* Mesure du temps */
    /*fin = clock();
    temps = (double)(fin - debut) / CLOCKS_PER_SEC;
    sprintf(buffer, "%s%s frame calculé en %f sec", MOTEUR, SUCC, temps);
    log_message(buffer);*/
}
#endif /*AFFICHAGE_C*/