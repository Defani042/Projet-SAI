#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "GL/gl.h"
#include "GL/glut.h"
#include "GL/freeglut_ext.h" 

#define PATH_TEXTURE_ENNEMI_A "fich/textures/Personnage/Antho.bmp"
#define PATH_TEXTURE_ENNEMI_S "fich/textures/Personnage/Adri.bmp"
#define PATH_TEXTURE_ENNEMI_T "fich/textures/Personnage/Gault.bmp"
#define PATH_TEXTURE_ENNEMI_D "fich/textures/Personnage/Dori.bmp"


extern GLuint texture_ennemi_A;
extern GLuint texture_ennemi_S;
extern GLuint texture_ennemi_T;
extern GLuint texture_ennemi_D;

void initialisation_texture();

GLuint load_texture(const char* filename);

#endif /*_TEXTURE_H_*/