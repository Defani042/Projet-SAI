#ifndef _LOG_H_
#define _LOG_H_
/*lib std*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

#include "config/config.h"

void creer_dossiers_log();

int creer_fichier_log();

void log_init();

void log_message(const char *msg);

void log_close();

int log_nettoyer();


#endif /*_LOG_H_*/