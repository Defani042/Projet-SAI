#ifndef _OBJET_C_
#define _OBJET_C_

#include "noyau/objet.h"


/*
R: création d'un objet
E: 1 TAD position
S: 1 TAD objet
A: Adrien
*/
objet creer_objet(position pos,double h,double l,double L){
    objet o = NULL;
    if ((o = (objet)malloc(sizeof(s_objet))) == NULL)
	{
        fprintf(stderr,"Erreur malloc par la fonction creer_objet()\n");
        log_message(NOYAU ERR "Erreur malloc par la fonction creer_objet()");
        exit(EXIT_FAILURE);
    }
    o->rot = SET_UP_ORIGINE_POS; /*on set les angle en 0 0 0*/
    o->hauteur = h;
    o->largeur = l;
    o->longueur = L;
    o->r = 1.0; /*par défaut les objets sont blancs*/
    o->g = 1.0;
    o->b = 1.0;
    o->pos = pos;
    o->next = NULL;
    o->parent = NULL;
    log_message(NOYAU SUCC "Objet créé");
    return o;
}


/*
R: suprimer un objet dans la liste
E: 1 TAD objet et un entier position 
S: 1 TAD objet sans l'objet cible (si celui ci n'existe pas on retourne le tableau)
A: Adrien
*/
objet supprimer_objet(objet head, int i)
{
    objet tmp;
    objet prev;
    int curpos;

    tmp = head;
    prev = NULL;
    curpos = 0;

    /* suppression de la tête */
    if (i == 0)
    {
        if (head == NULL)
            return NULL;

        tmp = head->next;
        liberer_position(head->pos);
        log_message(NOYAU WARN "Objet à supprimer non trouvé! supprimer_objet()");
        free(head);
        return tmp;
    }

    while (tmp != NULL && curpos < i)
    {
        prev = tmp;
        tmp = tmp->next;
        curpos++;
    }

    if (tmp == NULL)
    {
        fprintf(stderr, "Indice hors limite\n");
        
        return head;
    }

    prev->next = tmp->next;
    liberer_position(tmp->pos);
    free(tmp);

    return head;
}

/*
R: suprimer un objet dans la liste
E: 2 TAD objet la liste et l'objet qu'on veux suprimer
S: 1 TAD objet sans le iémé element (s'il n'y a pas d'objet d'indice i alors retourne la liste d'objet)
A: Adrien
*/
objet supprimer_objet_ptr(objet liste, objet cible){
    objet tmp = liste;
    objet prev = NULL;

    while (tmp != NULL)
    {
        if (tmp == cible)
        {
            /* réattachement de la liste */
            if (prev != NULL) prev->next = tmp->next;
             /* cas ou la cible était la tête */
            else liste = tmp->next; 
            liberer_position(tmp->pos);
            free(tmp);
            return liste; /* nouvelle tête */
        }

        prev = tmp;
        tmp = tmp->next;
    }

    /* cas ou la cible n'est pas trouvée */
    log_message(NOYAU WARN "Objet à supprimer non trouvé! supprimer_objet_ptr()");
    return liste;
    
}

/*
R: suprimer la liste
E: 1 TAD objet 
S: rien
A: Adrien
*/
void liberer_objet(objet o){
    objet tmp = o;
    while (o != NULL)
    {
        tmp = o->next;
        liberer_position(o->pos);
        free(o);
        o = tmp;
    }
    log_message(NOYAU SUCC "objet liberé !");
     
}

/*
R: concaténer deux objet
E: 2 TAD objet (o1 et o2)
S: 1 TAD objet (o1+o2)
A: Adrien
*/

objet concat_objet(objet o1 , objet o2){
    objet tmp = o1;
    if(o1 == NULL) return o2;
    if(o2 == NULL) return o1;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }

    tmp->next = o2;
    return o1;

}

/*
R: ajoute un objet en début de tableau
E: 2 TAD objet (o1 et o2)
S: 1 TAD objet (o1+o2)
A: Adrien
*/
objet ajouter_debut(objet liste, objet nouvel_objet)
{
    objet last;
    if (nouvel_objet == NULL)
        return liste;

    /* si nouvel_objet est une liste, on attache à la tête */
    last = nouvel_objet;
    while (last->next != NULL)
        last = last->next;

    last->next = liste;
    return nouvel_objet; /* nouvelle tête */
}

/*
R: ajoute un objet en fin de tableau
E: 2 TAD objet (o1 et o2)
S: 1 TAD objet (o1+o2)
A: Adrien
*/

objet ajouter_fin(objet liste, objet nouvel_objet)
{
    objet tmp;

    if (nouvel_objet == NULL)
        return liste;

    if (liste == NULL)
        return nouvel_objet;

    tmp = liste;
    while (tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = nouvel_objet;

    return liste;
}

/*
R: permet de récupérer un objet dans la liste 
E: 1 TAD objet et 1 entier l'indexe
S: 1 TAD objet 
A: Adrien
*/
objet obtenir_objet(objet liste, int index){
    int curpos = 0;
    objet tmp = liste;
    while (curpos!=index && tmp != NULL)
    {
        tmp = tmp->next;
        curpos ++;
    }
    if(curpos!=index){
        log_message(NOYAU WARN "Aucun objet trouver !");
    }
    return tmp;
    
}


/*
R: déterminer la taille des objet
E: 1 TAD objet 
S: 1 entier la taille de la liste
A: Adrien
*/
int taille_objet(objet o){
    objet tmp = o;
    int t =0;
    while (tmp!=NULL)
    {
        tmp = tmp->next;
        t++;
    }
    return t;
}

/*
R: afficher les objet sur le terminale
E: 1 TAD objet 
S: rien
A: Adrien
*/
void afficher_objets(objet liste){
    objet tmp = liste;
    int i=0;
    while (tmp!=NULL)
    {
        printf("/-ELEMENT %d-/",i);
        printf("POS(x = %f ,y= %f ,z= %f)\n",tmp->pos->x,tmp->pos->y,tmp->pos->z);
        printf("hauteur : %f\n",tmp->hauteur);
        printf("longueur : %f\n",tmp->longueur);
        printf("largeur : %f\n",tmp->largeur);
        i++;
        tmp = tmp->next;
    }

}

/*
R: permet de changer la couleur d'un objet
E: 1 TAD objet et 3 float pour les composantes de couleur
S: rien
A: Gaultier
*/
void couleur_objet(objet o, float r, float g, float b){
    if(o == NULL) return;
    o->r = r;
    o->g = g;
    o->b = b;
}

/*
R: copie un objet
E: 1 TAD objet
S: 1 TAD objet
A: Gaultier
*/
objet copier_objet(objet original) {
    objet copie = (objet)malloc(sizeof(s_objet));
    if (copie == NULL) {
        fprintf(stderr, "Erreur malloc\n");
        exit(1);
    }

    /* Copie champ par champ */
    copie->rot = original->rot;
    copie->pos = original->pos;
    copie->hauteur = original->hauteur;
    copie->largeur  = original->largeur;
    copie->longueur = original->longueur;
    copie->r = original->r;
    copie->g = original->g;
    copie->b = original->b;
    copie->parent = original->parent;

    /* Pour la copie dans la grille, on ne copie pas next */
    copie->next = NULL;

    return copie;
}


#endif /*_OBJET_C_*/