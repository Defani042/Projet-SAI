#ifndef AFFICHAGE_C
#define AFFICHAGE_C

#include "moteur/controle.h"


/*variables globales*/
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
int n = PADING;
int f = DIST_REND;
int largeur_ecran;
int hauteur_ecran;

int deja_libere = 0;
volatile sig_atomic_t should_exit = 0;
volatile sig_atomic_t signal_recu = 0;

/*
R: gestionn du handler en cas de fin
E: un entier le signale reçu
S: rien
A: Adrien
*/
void gestion_signal(int sig){
    signal_recu = sig;
    should_exit = 1;
}
/*
R: écriture dans les fichier de log
E: une chaine de caractere
S: rien
A: Adrien
*/
void fermer_fenetre() {
    /* STOP GLUT AVANT */
    glutIdleFunc(NULL);
    glutPassiveMotionFunc(NULL);
    log_message(INIT SUCC "Fermeture de la fenêtre...");
    liberer_jeux();
}

/*
R: libération du jeusx
E: une chaine de caractere
S: rien
A: Adrien
*/
void liberer_jeux(){
   
    if (deja_libere) return; /*portection*/
     deja_libere = 1;/*flag de sécurités*/
    /*zone de la meme à libérrer*/
    liberer_carte(carte_jeu);
    carte_jeu = NULL;
    log_message(NOYAU SUCC "libération grille statique...");
    if(grille_statique!=NULL)detruire_grille(grille_statique);
    log_message(NOYAU SUCC "grille statique libérer");
    log_message(NOYAU SUCC "libération grille dynamique");
    if(grille_dynamique!=NULL)detruire_grille(grille_dynamique);
    log_message(NOYAU SUCC "grille dynamique libérer");
    log_close();
     
}
/*
R: écriture dans les fichier de log
E: une chaine de caractere
S: rien
A: Adrien
*/

void sortie_propre(){
    char buffer[128];
    switch(signal_recu) {
        case SIGINT:
            log_message(INIT SUCC"Signal SIGINT reçu. Nettoyage..." );
            break;
        case SIGTERM:
            log_message(INIT SUCC"Signal SIGTERM reçu. Nettoyage...");
            break;
        case SIGSEGV:
            log_message(INIT SUCC"Signal SIGSEV reçu. Nettoyage...");
            log_message(INIT SUCC"Erreur de ségmentation...");
            exit(EXIT_FAILURE);
            break;
        default:
            if(interruption){
                sprintf(buffer, INIT SUCC"Signal d'arrêt reçu via le menu pause. Nettoyage...");
                log_message(buffer);
            }
            else{
                sprintf(buffer, INIT SUCC"Signal %d reçu. Nettoyage...", signal_recu);
                log_message(buffer);
            }
    }
    liberer_jeux();
    glutLeaveMainLoop();
}

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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutIdleFunc(animer);
    glutKeyboardFunc(touche_pressee);
    largeur_ecran = glutGet(GLUT_SCREEN_WIDTH);
    hauteur_ecran = glutGet(GLUT_SCREEN_HEIGHT);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutKeyboardUpFunc(touche_relachee);
    glutWarpPointer(largeur_ecran/2, hauteur_ecran/2);
    glutPassiveMotionFunc(mouvement_souris);
    glutMouseFunc(gerer_souris);
    glutMotionFunc(mouvement_souris);
}


/*
R: permet d'actualiser les images
E: rien
S: rien
A: Gaultier
*/
void animer(){
    clock_t current_time = clock();
    static clock_t last_time = 0;
    if (should_exit || interruption) {
        sortie_propre();
        return;
    }
    if (!(current_time - last_time < CLOCKS_PER_SEC / 60)){
        last_time = current_time;
        angle_soleil += 0.0001f;
        bas();
        avencer_vague_ennemi(carte_jeu);
        /*application de la logique du jeu*/
        regenerer_jetpack(carte_jeu->j);
        regeneration_vie(carte_jeu->j);
        raffraichir();
        glutPostRedisplay();
        maj_grille_dynamique(carte_jeu->liste_ennemi);
        if(taille_ennemi(carte_jeu->liste_ennemi) < NBMAX_ENNEMI){
            carte_jeu->liste_ennemi = ajouter_ennemi(creer_ennemi_alea(carte_jeu),carte_jeu->liste_ennemi);
        }
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
    /*glFrustum(l,r,b,top,n,f);*/
    gluPerspective(60.0f, (float)largeur_ecran / hauteur_ecran, 0.1f, f);

    /*Init de la matrice de visualisation*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ+2,eyeX+ directionX,eyeY + directionY,eyeZ + directionZ+2,upX,upY,upZ);

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

    /*Fin*/
    glutSwapBuffers();
   
   
    /*
    printf("NOMBRE OBJ dans la map: %d\n",taille_objet(carte_jeu->liste_objets)); 
    printf("POSITION DU JOUEUR SUR LA CARTE: (x:%f,y:%f)\n",carte_jeu->j->pos->x,carte_jeu->j->pos->y);
    printf("POSITION JOEUR DANS LA GRILLE : cellule[%d,%d]\n",coord_to_cell_x(carte_jeu->j->pos->x,grille_statique)
                                                            ,coord_to_cell_x(carte_jeu->j->pos->y,grille_statique)
    );
    */

    /* Mesure du temps */
    /*fin = clock();
    temps = (double)(fin - debut) / CLOCKS_PER_SEC;
    sprintf(buffer, "%s%s frame calculé en %f sec", MOTEUR, SUCC, temps);
    log_message(buffer);*/
}
#endif /*AFFICHAGE_C*/