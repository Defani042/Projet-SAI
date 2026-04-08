#ifndef _CYCLE_JOUR_NUIT_C_
#define _CYCLE_JOUR_NUIT_C_

#include "moteur/cycle_jour_nuit.h"
#include "moteur/composant3d.h"

/*
R : calcul la couleur en fonction de deux couleur et un facteur de mélange
E: 7 float (t, r1, g1, b1, r2, g2, b2) et 3 pointeur de float (r, g, b)
S: rien
A: Gaultier
*/
void calcul_couleur(float t,float r1, float g1, float b1,float r2, float g2, float b2,float *r, float *g, float *b){
    *r = r1 * (1.0f - t) + r2 * t;
    *g = g1 * (1.0f - t) + g2 * t;
    *b = b1 * (1.0f - t) + b2 * t;
}

/*
R: gère le cycle jour nuit en changeant la couleur du ciel et en affichant le soleil et la lune
E: rien
S: rien
A: Gaultier
*/
void cycle_jour_nuit() {
    float soleil_x = 950.0 * cos(angle_soleil);
    float soleil_y = 950.0 * sin(angle_soleil);
    float jr, jg, jb; /*couleur du jour*/
    float nr, ng, nb; /*couleur de la nuit*/
    float sr, sg, sb; /*couleur du lever du soleil*/
    float r, g, b;

    float t = (sin(angle_soleil) + 1.0f) / 2.0f; /*facteur pour mettre les bonnes couleurs*/

    /* couleurs */
    jr = 0.5f; jg = 0.8f; jb = 1.0f;
    nr = 0.0f; ng = 0.0f; nb = 0.2f;
    sr = 1.0f; sg = 0.5f; sb = 0.2f;

    if (t < 0.5f){
        calcul_couleur(t * 2.0f,nr, ng, nb,sr, sg, sb,&r, &g, &b);
    }
    else{
        calcul_couleur((t - 0.5f) * 2.0f,sr, sg, sb,jr, jg, jb,&r, &g, &b);
    }

    couleur_objet(ciel1, r, g, b);
    couleur_objet(ciel2, r, g, b);
    couleur_objet(ciel3, r, g, b);
    couleur_objet(ciel4, r, g, b);
    couleur_objet(ciel5, r, g, b);
    couleur_objet(ciel6, r, g, b);

    sphere(soleil_x, 0, soleil_y, 30.0, 0.7f, 0.7f, 0);
    sphere(-soleil_x, 0, -soleil_y, 30.0, 0.9f, 0.9f, 0.6f);
}

#endif /* _CYCLE_JOUR_NUIT_C_ */