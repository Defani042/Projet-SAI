#ifndef CONTROLE_C
#define CONTROLE_C

#include "moteur/controle.h"

/*
R: Permet d'avancer
E: rien
S: rien 
A: Gaultier
*/
void avancer(){
    eyeX++;
    xO++;
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
    eyeX--;
    xO--;
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
R: Permet de gerer toutes les touches du clavier
E: la touche et les coordonnées de la souris
S: rien
A: Gaultier
*/
void gerer_clavier(unsigned char touche, int x, int y){
    switch(touche){
        case 'Z' :
        case 'z' : avancer();break;

        case 'Q' :
        case 'q' : gauche();break;

        case 'S' :
        case 's' : reculer();break;

        case 'D' :
        case 'd' : droite();break;
    }
}

/*
R: Permet de gerer toutes les touches de la souris
E: la touche , l'etat et les coordonnées de la souris
S: rien
A: Gaultier
*/
void gerer_souris(int bouton, int etat, int x, int y){}

#endif /*CONTROLE_C*/