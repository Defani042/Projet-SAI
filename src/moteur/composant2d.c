#ifndef _COMPOSANT2D_C_
#define _COMPOSANT2D_C_

#include "moteur/composant2d.h"
/*
R: permet d'afficher un rectangle
E: 8 float (les coordonné x,y)(la taille w et h)(les rgb + transparence)
S: rien
A: Adrien
*/
void draw_rect(float x, float y, float w, float h, float r, float g, float b, float a)
{
    glColor4f(r, g, b,a);
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
R: permet d'avoir la largeur du texte
E: une chaine de caractère
S: la largueur du texte
A: Adrien
*/
float get_text_width(const char* text)
{
    const char* tmp;
    float width;

    tmp = text;
    width = 0.0f;

    while (*tmp)
    {
        width += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, *tmp);
        tmp++;
    }

    return width;
}

/*
R: permet d'afficher du texte surligné
E: 2 float (les coordonné x,y) et une chaine de caractère
S: rien
A: Adrien
*/
void draw_text_underlined(float x, float y, const char* text)
{
    float width;

    /* Dessine le texte */
    draw_text(x, y, text);

    /* Calcule la largeur */
    width = get_text_width(text);

    /* Dessine le soulignement */
    glBegin(GL_LINES);
        glVertex2f(x, y + UNDERLINE_OFFSET);
        glVertex2f(x + width, y + UNDERLINE_OFFSET);
    glEnd();
}

/*
R: permet d'afficher du texte en couleur 
E: 2 float (les coordonné x,y) et une chaine de caractère et 3 float (la couleur R G B)
S: rien
A: Adrien
*/
void draw_text_color(float x, float y, const char* text, float r, float g, float b)
{
    /* Déclarations C89 */
    const char* tmp;

    /* Couleur */
    glColor3f(r, g, b);

    /* Position */
    glRasterPos2f(x, y);

    /* Dessin */
    tmp = text;
    while (*tmp)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *tmp);
        tmp++;
    }
}

/*
R: permet d'afficher du texte surligné en couleur 
E: 2 float (les coordonné x,y) et une chaine de caractère et 3 float (la couleur R G B)
S: rien
A: Adrien
*/
void draw_text_underlined_color(float x, float y, const char* text,float r, float g, float b)
{
    float width;

    /* Largeur du texte */
    width = get_text_width(text);
  
    /* Dessin du texte */
    draw_text_color(x, y, text,r,g,b);

    /* Couleur */
    glColor3f(r, g, b);
    /* Soulignement */
    glBegin(GL_LINES);
        glVertex2f(x, y + UNDERLINE_OFFSET);              /* offset propre */
        glVertex2f(x + width, y + UNDERLINE_OFFSET);
    glEnd();
}

/*
R: permet d'afficher un cercle
E: 3 float (les coordonné x,y du centre du cercle et le rayon du cercle) 1 entier nombre de segment
S: rien
A: Adrien
*/
void draw_circle(float cx, float cy, float r, int num_segments)
{
    int i;
    glBegin(GL_LINE_LOOP); /* cercle (contour) */
    glColor3f(1.0f, 1.0f, 1.0f); /*couleur blanc*/
    for(i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * M_PI * (float)i / (float)num_segments;
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}


/*
R: permet d'afficher un disque
E: 3 float (les coordonné x,y du centre du cercle et le rayon du cercle) 1 entier nombre de segment
S: rien
A: Adrien
*/
void draw_disk(float cx, float cy, float r, int num_segments)
{
    int i;
    glBegin(GL_TRIANGLE_FAN); /* disque rempli */
    glColor3f(1.0f, 1.0f, 1.0f); /*couleur blanc*/
    glVertex2f(cx, cy); /* centre du disque */
    for(i = 0; i <= num_segments; i++)
    {
        float theta = 2.0f * M_PI * (float)i / (float)num_segments;
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

/*
R: permet d'afficher un cercle de couleur
E: 3 float (les coordonées x,y du centre du cercle et le rayon du cercle), 1 entier nombre de segments, 3 float couleur r,g,b
S: rien
A: Adrien
*/
void draw_colored_circle(float cx, float cy, float radius, int num_segments, float r_col, float g_col, float b_col)
{
    int i;
    glBegin(GL_LINE_LOOP); /* cercle (contour) */
    glColor3f(r_col, g_col, b_col); /* couleur du cercle */
    for(i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * M_PI * (float)i / (float)num_segments;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

/*
R: permet d'afficher un disque rempli de couleur
E: 3 float (coordonnées x, y du centre, rayon du disque), 1 entier nombre de segments, 3 float couleur r, g, b
S: rien
A: Adrien
*/
void draw_colored_disk(float cx, float cy, float radius, int num_segments, float r_col, float g_col, float b_col)
{
    int i;
    glBegin(GL_TRIANGLE_FAN); /* disque rempli */
    glColor3f(r_col, g_col, b_col); /* couleur du disque */
    glVertex2f(cx, cy); /* centre du disque */
    for(i = 0; i <= num_segments; i++)
    {
        float theta = 2.0f * M_PI * (float)i / (float)num_segments;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

/*
R: affiche un texte centrer sur un point x,y    
E: 1 char(le texte) 5 float(le point de centrage(x,y) la taille et la couleur (r,g,b))
S: rien
A: Adrien
*/
void afficher_texte_centre(const char *texte, float x_centre, float y_centre, float scale, float r, float g, float b)
{
    float largeur = 0.0f;
    int i;

    /* calcul de la largeur totale du texte */
    for (i = 0; texte[i] != '\0'; i++)
        largeur += glutStrokeWidth(GLUT_STROKE_ROMAN, texte[i]);

    /* couleur du texte */
    glColor3f(r, g, b);

    glPushMatrix();
        /* recentrer le texte */
        glTranslatef(x_centre - (largeur * scale / 2), y_centre, 0.0f);
        glScalef(scale, -scale, 1.0f); /*application de la taille*/

        /* afficher chaque caractère */
        for (i = 0; texte[i] != '\0'; i++)
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, texte[i]);
    glPopMatrix();
}

/*
R: afficher une popup
E: 1 char(le texte) 1 entier durer de la popus 3 float( la couleur (r,g,b))
S: rien
A: Adrien
*/
void afficher_popup(const char *popup_texte, int popup_fin_time,float r,float g,float b)
{
    int t = glutGet(GLUT_ELAPSED_TIME);
    if (t < popup_fin_time)  /*tant que le temps n'est pas écoulé*/
    {
        /*Affiche le texte centré*/
        afficher_texte_centre(popup_texte, largeur_ecran / 2, hauteur_ecran / 2, 0.3f,r,g,b);
    }
}
#endif /*_COMPOSANT2D_C_*/