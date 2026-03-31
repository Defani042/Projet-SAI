#ifndef CONTROLE_C
#define CONTROLE_C

#include "moteur/controle.h"

int touches[256] = {0};

int derX = 0, derY = 0;
float camX = -90.0f;
float camY = 0.0f;

/*vecteur de direction*/
float directionX;
float directionY;
float directionZ;

/*position pour le deplacement*/
float positionX = 0.0f;
float positionY = 0.0f;

/*direction ou le joueur regarde*/
float angle_direction;

/*competence choisie*/
int competence = 0;

/*Demande d'interruption*/
int interruption = 0;

/*
R: Permet d'avancer
E: rien
S: rien 
A: Gaultier et Adrien
*/
void avancer() {

    joueur j = carte_jeu->j;
    if (carte_jeu == NULL || carte_jeu->j == NULL){
        log_message(MOTEUR WARN "Joueur NULL! fonction avancer()");
        return;
    }
        
    deplacer_joueur(carte_jeu, 1.0, 0.0, 0.0);

    /*Mise à jour de la caméra pour OpenGL*/ 
    eyeX = (int)j->pos->x;
    eyeY = (int)j->pos->y;
    eyeZ = (int)j->pos->z;
    eyeX += directionX;
    eyeY += directionY;
    eyeZ += directionZ;
}

/*
R: Permet d'aller à gauche
E: rien
S: rien 
A: Gaultier et Adrien
*/
void gauche(){

    joueur j = carte_jeu->j;
    if (carte_jeu == NULL || carte_jeu->j == NULL){
        log_message(MOTEUR WARN "Joueur NULL! fonction gauche()");
        return;
    }
    

    deplacer_joueur(carte_jeu, 0.0, 1.0, 0.0);

    /*Mise à jour de la caméra pour OpenGL*/ 
    eyeX = (int)j->pos->x;
    eyeY = (int)j->pos->y;
    eyeZ = (int)j->pos->z;
    eyeX -= directionY;
    eyeY += directionX;
}

/*
R: Permet de reculer
E: rien
S: rien 
A: Gaultier et Adrien
*/
void reculer(){
    joueur j = carte_jeu->j;
    if (carte_jeu == NULL || carte_jeu->j == NULL){
        log_message(MOTEUR WARN "Joueur NULL! fonction reculer()");
        return;
    }
    

    deplacer_joueur(carte_jeu, -1.0, 0.0, 0.0);

    /*Mise à jour de la caméra pour OpenGL*/ 
    eyeX = (int)j->pos->x;
    eyeY = (int)j->pos->y;
    eyeZ = (int)j->pos->z;

    eyeX -= directionX;
    eyeY -= directionY;

}

/*
R: Permet d'aller à droite
E: rien
S: rien 
A: Gaultier et Adrien
*/
void droite(){
    joueur j = carte_jeu->j;
    if (carte_jeu == NULL || carte_jeu->j == NULL){
        log_message(MOTEUR WARN "Joueur NULL! fonction droite()");
        return;
    }

    deplacer_joueur(carte_jeu, 0.0, -1.0, 0.0);

    /*Mise à jour de la caméra pour OpenGL*/ 
    eyeX = (int)j->pos->x;
    eyeY = (int)j->pos->y;
    eyeZ = (int)j->pos->z;
    eyeX += directionY;
    eyeY -= directionX;
}

/*
R: Permet de monter
E: rien
S: rien 
A: Gaultier et Adrien
*/
void haut(){
    joueur j = carte_jeu->j;
    if (carte_jeu == NULL || carte_jeu->j == NULL){
        log_message(MOTEUR WARN "Joueur NULL! fonction haut()");
        return;
    }
    if(j->jetpack>0){
        deplacer_joueur(carte_jeu, 0.0, 0.0, 2.0);
        utiliser_jetpack(j);
    }

    /*Mise à jour de la caméra pour OpenGL*/ 
    eyeX = (int)j->pos->x;
    eyeY = (int)j->pos->y;
    eyeZ = (int)j->pos->z;
    eyeZ++;
}

/*
R: Permet de descendre
E: rien
S: rien 
A: Gaultier et Adrien
*/
void bas(){
    joueur j = carte_jeu->j;
    if (carte_jeu == NULL || carte_jeu->j == NULL){
        log_message(MOTEUR WARN "Joueur NULL! fonction bas()");
        return;
    }
    reapparition(j);
    
    deplacer_joueur(carte_jeu, 0.0, 0.0, -0.5);

    /*Mise à jour de la caméra pour OpenGL*/ 
    eyeX = (int)j->pos->x;
    eyeY = (int)j->pos->y;
    eyeZ = (int)j->pos->z;
    eyeZ--;
}

/*
R: affichage du menu debug
E: rien
S: rien 
A: Adrien
*/
void show_debug_menu(){
    if(show_menu_debug == 0){
        show_menu_debug = 1;
    }
    else{
        show_menu_debug = 0;
    }
}

/*
R: affichage du menu debug
E: rien
S: rien 
A: Gaultier
*/
void show_menu_upgrade(){
    if(aff_amelioration == 0){
        aff_amelioration = 1;
        glutPassiveMotionFunc(NULL);
        glutSetCursor(GLUT_CURSOR_INHERIT);
    }
    else{
        aff_amelioration = 0;
        glutPassiveMotionFunc(mouvement_souris);
        glutSetCursor(GLUT_CURSOR_NONE);
        glutIdleFunc(animer);
    }
}

/*
R: Permet de mettre à jour le tableau de touches actives
E: la touche et les coordonnées de la souris
S: rien
A: Gaultier et Adrien
*/
void touche_pressee(unsigned char touche, int x, int y) {
    (void)x; /*pour le warning de non use */
    (void)y; /*pour le warning de non use */
    touches[touche] = 1;
    if(touche == 'k'){
        show_debug_menu();
    }
    if(touche == 27){ /*echap*/
        show_menu_upgrade();
    }
}

/*
R: Permet de reset le tableau de touches actives
E: la touche et les coordonnées de la souris
S: rien
A: Gaultier
*/
void touche_relachee(unsigned char touche, int x, int y) {
    (void)x; /*pour le warning de non use */
    (void)y; /*pour le warning de non use */
    touches[touche] = 0;
}

/*
R: Permet de gerer toutes les touches du clavier
E: la touche et les coordonnées de la souris
S: rien
A: Gaultier
*/
void raffraichir() {

    if (touches['z'] || touches['Z'])
        avancer();

    if (touches['s'] || touches['S'])
        reculer();

    if (touches['q'] || touches['Q'])
        gauche();

    if (touches['d'] || touches['D'])
        droite();

    if (touches[' '])
        haut();

    if (touches['c'] || touches['C'])
        bas();
}

/*
R: Permet de gerer toutes les touches de la souris
E: la touche , l'etat et les coordonnées de la souris
S: rien
A: Gaultier
*/
void gerer_souris(int bouton, int etat, int x, int y){
    if(bouton == 0 && etat == 1 && aff_amelioration){
        if(x > largeur_ecran/2-200 && x < largeur_ecran/2+200){
            if(y > hauteur_ecran/2-180 && y < hauteur_ecran/2-80){
                competence = 1;
                show_menu_upgrade();
            }
            if(y > hauteur_ecran/2-40 && y < hauteur_ecran/2+60){
                competence = 2;
                show_menu_upgrade();
            }
            if(y > hauteur_ecran/2+110 && y < hauteur_ecran/2+210){
                competence = 3;
                show_menu_upgrade();
            }
            printf("Amélioration %d choisie\n",competence);
        }
        if(x > largeur_ecran - 20 && y < 20){
            show_menu_upgrade();
            glutPostRedisplay();
            interruption = 1;
        }
    }
}

/*
R: Permet de gerer le mouvement de la souris
E: les coordonnées de la souris
S: rien
A: Gaultier et Adrien
*/
void mouvement_souris(int x, int y){
    int dx = x - derX; /*distance de deplacement de la souris*/
    int dy = y - derY;
    float rad_camY;
    joueur j;

    j = carte_jeu->j;
    derX = x;
    derY = y;

    /*if pour les deplacement trop grand (comme le reset de la souris)*/
    if((dx < 100 && dx > -100) && (dy < 100 && dy > -100)){

        camX -= dx;
        camY -= dy;

        if (camY > 89.0f) camY = 89.0f;     /*pour ne pas tourner à 360 degres*/
        if (camY < -89.0f) camY = -89.0f;   /*à la vertical*/

        rad_camY = camY * M_PI / 180.0f;        /*calcul des direction*/
        angle_direction = camX * M_PI / 180.0f; 

        directionX = cos(rad_camY) * cos(angle_direction); /*application des */
        directionY = cos(rad_camY) * sin(angle_direction); /*direction aux vecteur*/
        directionZ = sin(rad_camY);
        j->dir->x = directionX;
        j->dir->y = directionY;
        j->dir->z = directionZ;

    }
    /*si la souris touche les bors de l'ecran, elle reviens au centre*/
    if(x == 0 || y == 0 || x == largeur_ecran -1 || y == hauteur_ecran - 1){
        glutWarpPointer(largeur_ecran/2, hauteur_ecran/2);  
    }
    
}

#endif /*CONTROLE_C*/