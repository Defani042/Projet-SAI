#ifndef _TEXTURE_C_
#define _TEXTURE_C_

#include "moteur/texture.h"
#include "log/log.h"
#include "config/config.h"

#include <stdio.h>
#include <GL/glut.h>

GLuint texture_ennemi_A;
GLuint texture_ennemi_S;
GLuint texture_ennemi_T;

void initialisation_texture() {
    texture_ennemi_A = load_texture(PATH_TEXTURE_ENNEMI_A);
    texture_ennemi_S = load_texture(PATH_TEXTURE_ENNEMI_S);
    texture_ennemi_T = load_texture(PATH_TEXTURE_ENNEMI_T);
}

GLuint load_texture(const char *filename){
    FILE *file;
    unsigned char header[54];
    unsigned char *data;
    int width, height;
    int imageSize;
    int retour;
    GLuint texture;

    file = fopen(filename, "rb");
    if (!file)
    {
        log_message(MOTEUR ERR "Erreur ouverture fichier de texture\n");
        return 0;
    }

    retour = fread(header, 1, 54, file);
    if (retour != 54)
    {
        log_message(MOTEUR ERR "Erreur lecture en-tête fichier de texture\n");
        return 0;
    }

    width  = *(int*)&header[18];
    height = *(int*)&header[22];
    imageSize = 3 * width * height;

    data = (unsigned char*)malloc(imageSize);
    retour = fread(data, 1, imageSize, file);
    if (retour != imageSize)
    {
        log_message(MOTEUR ERR "Erreur lecture données fichier de texture\n");
        free(data);
        fclose(file);
        return 0;
    }
    fclose(file);

    /* BMP = BGR → convertir en RGB */
    {
        int i;
        for (i = 0; i < imageSize; i += 3)
        {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
        }
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 width, height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    free(data);
    log_message(MOTEUR SUCC "Texture chargée avec succès");
    return texture;
}

#endif /*_TEXTURE_C_*/