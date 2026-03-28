#ifndef _INTERFACE_C_
#define _INTERFACE_C_

#include"moteur/interface.h"

/*varaible globale*/
clock_t timer = 0;
int show_menu_debug = 0;

/*variable pour compter le nombre de FPS*/
static int frame_count = 0;
static double last_time = 0.0;
static double fps = 0.0;


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
    sprintf(buffer, "PV : %d / %d", (int)j->vie, (int)j->vie_max);
    draw_text(x + 50, y + 16, buffer);
}

/*
R: permet d'afficher la bare du jetpack
E: vide
S: rien
A: Adrien
*/
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
    sprintf(buffer, " Jet : %d / %d", (int)j->jetpack, (int)j->jetpack_max);
    draw_text(x + 50, y + 16, buffer);
}

/*
R: permet d'afficher l'xp
E: vide
S: rien
A: Adrien
*/
void afficher_xp(int screen_width){
    char buffer[32];
    joueur j = carte_jeu->j;

    /* Taille de la barre */
    float largeur = 220;
    float hauteur = 20;

    /* Position centrée en haut */
    float x = (screen_width - largeur) / 2.0f; /*centrée horizontalement*/
    float y = 20; /*distance depuis le haut de l'écran*/

    /* Ratio pour le remplissage (XP ou jetpack) */
    float ratio = j->niv / j->seuil; /*proportion*/ 

    /* Affichage fond gris */
    draw_rect(x, y, largeur, hauteur, 0.2f, 0.2f, 0.2f);

    /* Affichage du jetpack/fond bleu */
    draw_rect(x + 10, y + 4, (largeur - 20) * ratio, hauteur - 8, 0.0f, 0.1f, 1.0f);

    /* Texte sur la barre (XP ou jetpack) */
    sprintf(buffer, "%d / %d", (int)j->xp, (int)j->seuil);
    draw_text(x + (largeur / 2) - 30, y + 16, buffer); /*centré approximativement*/ 

    /* Affichage du niveau sous la barre */
    sprintf(buffer, "Niveau %d", j->niv);
    draw_text(x + (largeur / 2) - 40, y + hauteur + 15, buffer); /*centré horizontalement*/
}



/*
R: permet de mettre à jour les fps
E: vide
S: rien
A: Adrien
*/
void maj_fps()
{   
    double current_time;
    frame_count++;

    current_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0; 
    if (current_time - last_time >= 1.0)/*actualisation toutes les seconde*/
    {
        fps = frame_count / (current_time - last_time);
        frame_count = 0;
        last_time = current_time;
    }
}

/*
R: permet d'afficher les FPS
E: vide
S: rien
A: Adrien
*/
void afficher_fps()
{
    char buffer[32];
    sprintf(buffer, "FPS: %.2f", fps);
    draw_text(largeur_ecran -120,40, buffer); /*coin en haut à droite*/
}

/*
R: permet d'afficher la position du joueur dans l'espace
E: vide
S: rien
A: Adrien
*/
void afficher_pos(){
    char buffpos[64];
    float x = largeur_ecran -120;            
    float y = 80;
    joueur j = carte_jeu->j;
    /*desin de la position*/
    draw_text(x +20, y, "Position:");
    sprintf(buffpos, "x:%d y:%d z:%d", (int)j->pos->x,(int)j->pos->y,(int)j->pos->z);
    draw_text(x,y+30, buffpos);
}

/*
R: permet d'afficher le nombre d'objet
E: vide
S: rien
A: Adrien
*/
void afficher_nb_obj(){
    char buffer[32];
    sprintf(buffer, "OBJ: %d", nb_obj);
    draw_text(largeur_ecran -100,180, buffer); /*coin en haut à droite*/
}

/*
R: permet d'afficher le timmer
E: vide
S: rien
A: Adrien
*/
void afficher_timmer(){
    char buffer[32];
    int min,sec,heur;
    float x = 400;
    float y = 20;
    /*calcul du timer*/
    clock_t maintenant = clock(); /*temps actuel*/
    float secondes = (float)(maintenant - timer) / CLOCKS_PER_SEC;
    heur = (int)(secondes / 3600);
    min  = ((int)secondes % 3600) / 60;
    sec  = (int)secondes % 60;
    /*desin du timmer*/
    sprintf(buffer, "%02d:%02d:%02d",heur,min,sec);
    draw_text(x,y+20, buffer);
    
}
  
/*
R: permet d'afficher le nombre d'ennemie
E: vide
S: rien
A: Adrien
*/
void afficher_nb_ennemie(){
    char buffer[32];
    float x = largeur_ecran - 100;
    float y = 140;
    /*desin du timmer*/
    sprintf(buffer, "Ennemi: %d",taille_ennemi(carte_jeu->liste_ennemi));
    draw_text(x,y, buffer);
    
}

void afficher_menu_debug(){
    draw_rect(largeur_ecran-160,0,160,200,0,0,0);
    draw_text(largeur_ecran-100,20, "DEBUG" );
    afficher_fps();
    afficher_pos();
    afficher_nb_ennemie();
    afficher_nb_obj();
    maj_fps();
    afficher_fps();
    
}


/*
R: permet d'afficher l'interface
E: vide
S: rien
A: Adrien
*/
void afficher_interface(){
    if(show_menu_debug){
        afficher_menu_debug();
    }
    afficher_vie();
    afficher_jet();
    afficher_timmer();
    afficher_xp(largeur_ecran);
}

#endif /*_INTERFACE_C_*/