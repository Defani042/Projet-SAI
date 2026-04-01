#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdio.h>
#include <stdlib.h>

#define SET_UP_ORIGINE_POS creer_position(0,0,0)

/*MACRO UTILISATION*/
#define USE_JET_PACK .1
#define VOID_DAMAGE 10

/*affichage*/
#define DIST_REND 3000.0
#define PADING 15

/*COULDOWN DE  REGENERATION*/
#define DURRER_JET 5
#define DURRER_VIE 5
/*OFFSET DU SOULIGNAGE*/
#define UNDERLINE_OFFSET 3.0f



/*OBJ CENTRER OU NON*/
#define CENTRER 1
#define NO_CENTRER 0


/*definiation de la hitbox du joueur*/
#define LONG 2.0
#define LARG 2.0
#define HAUT 2.0


/*CAPACITER DU JOUEUR*/
#define CAP_DEF 0
#define CAP_VIE 1 
#define CAP_ATK 2
#define CAP_REG 3
#define CAP_JET 4
#define CAP_VIT 5
#define CAP_TAUX_CRIT 6
#define CAP_DEGATS_CRIT 7


/*LOG*/
#define LOG_FILE_PATH "fich/log/log.txt"
#define INIT "[INIT]: "
#define ERR "(ERREUR): "
#define WARN "(WARN): "
#define SUCC "(SUCCES): "
#define MOTEUR "[MOTEUR]: "
#define NOYAU "[NOYAU]: "
#define LOG "[LOG]: "
#define INFO "[INFO]: "

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


#define NBMAX_ENNEMI 5
#define NB_MAX 128

/* ---------- GRILLE ---------- */

/* Taille maximale de la carte (en unité du monde) */
#define CARTE_MAX_X 3000
#define CARTE_MAX_Y 3000

/* Taille d'une cellule de la grille */
#define CELL_SIZE 100.0

/* Nombre de cellules sur X et Y (calculé depuis la carte et la taille de cellule) */
#define TAILLE_GRILLE_X ((CARTE_MAX_X / CELL_SIZE) + 1)
#define TAILLE_GRILLE_Y ((CARTE_MAX_Y / CELL_SIZE) + 1)

/* Messages de log spécifiques à la grille */
#define GRILLE_SUCC NOYAU SUCC "Grille initialisée"
#define GRILLE_ERR  NOYAU ERR  "Erreur lors de la création de la grille"



#endif /*_CONFIG_H_*/