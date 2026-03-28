#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdio.h>
#include <stdlib.h>

#define SET_UP_ORIGINE_POS creer_position(0,0,0)
#define USE_JET_PACK .1

/*affichage*/
#define DIST_REND 3000.0

/*COULDOWN DE  REGENERATION*/
#define DURRER_JET 3


#define PADING 15


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


/*LOG*/
#define LOG_FILE_PATH "fich/log/log.txt"
#define INIT "[INIT]: "
#define ERR "(ERREUR): "
#define WARN "(WARN): "
#define SUCC "(SUCCES): "
#define MOTEUR "[MOTEUR]: "
#define NOYAU "[NOYAU]: "
#define LOG "[LOG]: "

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


#define NBMAX_ENNEMI 5



#endif /*_CONFIG_H_*/