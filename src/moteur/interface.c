#ifndef _INTERFACE_C_
#define _INTERFACE_C_

#include"moteur/interface.h"

/*
R: permet d'afficher un rectangle
E: 7 float (les coordonné x,y)(la taille w et h)(les rgb)
S: rien
A: Adrien
*/
void draw_rect(float x, float y, float w, float h, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

/*
R: permet d'afficher du texte
E: 2 float (les coordonné x,y) et une chaine de caractère
S: rien
A: Adrien
*/
void draw_text(float x, float y, const char* text)
{
    glColor3f(1.0f, 1.0f, 1.0f); /*couleur blanc*/
    glRasterPos2f(x, y);         /*position*/
    /*affichage du texte*/
    while (*text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}

/*
R: permet d'afficher la bare de vie 
E: vide
S: rien
A: Adrien
*/
void afficher_vie()
{
    char buffer[32];
    joueur j = carte_jeu->j;
    /*position de la barre de vie sur l'ecran*/
    float x = 20;            
    float y = 20;            
    float largeur = 220;
    float hauteur = 20;

    float ratio = j->vie / j->vie_max; /*proportion de vie restante au joueur*/

    /*affichage fon gris*/
    draw_rect(x, y, largeur,hauteur, 0.2f, 0.2f, 0.2f);

    /*affichage de la vie fond rouge*/
    draw_rect(x+10, y+4, (largeur-20) * ratio,hauteur-8, 1.0f, 0.0f, 0.0f);

   
    /*texte sur la barre*/
    sprintf(buffer, "%d / %d", (int)j->vie, (int)j->vie_max);
    draw_text(x + 50, y + 16, buffer);
}

void afficher_jet()
{
    char buffer[32];
    joueur j = carte_jeu->j;
    /*position de la barre de vie sur l'ecran*/
    float x = 20;            
    float y = 50;
    float largeur = 220;
    float hauteur = 20;   
    
    float ratio = j->jetpack / j->jetpack_max; /*proportion de vie restante au joueur*/

    /*affichage fon gris*/
    draw_rect(x, y, largeur,hauteur, 0.2f, 0.2f, 0.2f);

    /*affichage du jet pack fond bleu*/
    draw_rect(x+10, y+4, (largeur-20) * ratio,hauteur-8, 0.0f, 0.0f, 1.0f);
    
    /*texte sur la barre*/
    sprintf(buffer, "%d / %d", (int)j->jetpack, (int)j->jetpack_max);
    draw_text(x + 50, y + 16, buffer);
}
/*
R: permet d'afficher l'interface
E: vide
S: rien
A: Adrien
*/
void afficher_interface(){
    afficher_vie();
    afficher_jet();
}

#endif /*_INTERFACE_C_*/