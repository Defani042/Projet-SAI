#ifndef _ENNELI_C_
#define _ENNELI_C_

#include "noyau/ennemi.h"

/*
R: création d'un ennemi
E: 1 TAD position et 1 TAD objet
S: 1 TAD ennemie
A: Adrien
*/
ennemi creer_ennemi(objet o){
    ennemi e = NULL;
    if ((e = (ennemi)malloc(sizeof(s_ennemi))) == NULL)
	{
        fprintf(stderr,"Erreur malloc par la fonction creer_ennemi()\n");
        log_message(NOYAU ERR "Erreur malloc par la fonction creer_ennemi()");
        exit(EXIT_FAILURE);
    }
    e->obj = o;
    e->degat = 5;
    e->next =NULL;
    e->vit = VIT_E;
    e->vie = VIE_E;
    log_message(NOYAU SUCC "ennemie créé");
    return e;
}

/*
R: suprimer un ennemi dans la liste
E: 2 TAD ennemi la liste et l'objet qu'on veux suprimer
S: 1 TAD ennemi sans l'element cible (s'il n'y a pas d'ennemi cible alors retourne la liste d'objet)
A: Adrien
*/
ennemi supprimer_ennemi_ptr(ennemi head, ennemi cible){
    ennemi tmp = head;
    ennemi prev = NULL;

    while(tmp != NULL){
        if (tmp == cible){
            if (prev == NULL){
                /*suppression de la tête*/
                head = tmp->next;
            } else {
                prev->next = tmp->next;
            }

            liberer_objet(tmp->obj);
            free(tmp);
            return head;
        }

        prev = tmp;
        tmp = tmp->next;
    }

    log_message(NOYAU WARN "ennemi à supprimer non trouvé! supprimer_ennemi_ptr()");
    return head;
}


/*
R: suppression d'un ennemi
E: 1 TAD ennemie
S: rien
A: Adrien
*/
void liberer_ennemi(ennemi e){
    ennemi tmp = e->next;
    while(e != NULL){
        tmp = e->next;
        liberer_objet(e->obj);
        free(e);
        e = tmp;
    }
    log_message(NOYAU SUCC "Ennemi libéré");
}

/*
R: ajouter un ennemi dans la liste chainné 
E: 1 TAD ennemie
S: rien
A: Adrien
*/
ennemi ajouter_ennemi(ennemi e1,ennemi e2){
    /*je coupe ennemi 1*/
    if(e1->next!=NULL){
        liberer_ennemi(e1->next);
        log_message(NOYAU WARN "vous ne pouvez ajouter qu'un ennemie à la fois");
        log_message(NOYAU WARN "le reste de e1 est lebérer en mémoire");
    }
    e1->next = e2;
    return e1;
}

/*
R: verifie si un ennemie est mort
E: 1 TAD ennemie
S: 1 si il est mort sinon 0
A: Adrien
*/
int mort(ennemi e){
    if(e==NULL){
        return 1;
    }
    return e->vie <= 0;  
}


/*
R: donne la taille de la liste des ennemis
E: 1 TAD ennemie
S: 1 entier la taille 
A: Adrien
*/
int taille_ennemi(ennemi e){
    int t =0;
    ennemi tmp =e;
    while (tmp!=NULL)
    {
        t++;
        tmp = tmp->next;
    }
    return t;

}










#endif /*_ENNELI_C_*/