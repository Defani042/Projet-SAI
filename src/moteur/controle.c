#ifndef CONTROLE_C
#define CONTROLE_C

#include "moteur/controle.h"

int touches[256] = {0};

int derX = 0, derY = 0;
float camX = -90.0f;
float camY = 0.0f;

float directionX = 0.0f;
float directionY = 0.0f;
float directionZ = -1.0f;

/*
R: Permet d'avancer
E: rien
S: rien 
A: Gaultier
*/
void avancer(){
    eyeX--;
    xO--;
}

/*
R: Permet d'aller à gauche
E: rien
S: rien 
A: Gaultier
*/
void gauche(){
    eyeY--;
    yO--;
}

/*
R: Permet de reculer
E: rien
S: rien 
A: Gaultier
*/
void reculer(){
    eyeX++;
    xO++;
}

/*
R: Permet d'aller à droite
E: rien
S: rien 
A: Gaultier
*/
void droite(){
    eyeY++;
    yO++;
}

/*
R: Permet de monter
E: rien
S: rien 
A: Gaultier
*/
void haut(){
    eyeZ++;
    zO++;
}

/*
R: Permet de descendre
E: rien
S: rien 
A: Gaultier
*/
void bas(){
    eyeZ--;
    zO--;
}

/*
R: Permet de mettre à jour le tableau de touches actives
E: la touche et les coordonnées de la souris
S: rien
A: Gaultier
*/
void touche_pressee(unsigned char touche, int x, int y) {
    (void)x; /*pour le warning de non use */
    (void)y; /*pour le warning de non use */
    touches[touche] = 1;
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
    /*printf pour le warning de non use */
    printf("Bouton: %d, Etat: %d, X: %d, Y: %d\n", bouton, etat, x, y);
}

/*
R: Permet de gerer le mouvement de la souris
E: les coordonnées de la souris
S: rien
A: Gaultier
*/
void mouvement_souris(int x, int y){
    int dx = x - derX;
    int dy = y - derY;
    float rad_camX;
    float rad_camY;

    derX = x;
    derY = y;

    if((dx < 10 && dx > -10) || (dy < 10 && dy > -10)){

        camX -= dx;
        camY -= dy;

        if (camY > 89.0f) camY = 89.0f;
        if (camY < -89.0f) camY = -89.0f;

        rad_camY = camY * M_PI / 180.0f;
        rad_camX = camX * M_PI / 180.0f;

        directionX = cos(rad_camY) * cos(rad_camX);
        directionY = cos(rad_camY) * sin(rad_camX);
        directionZ = sin(rad_camY);

    }
    
}

#endif /*CONTROLE_C*/