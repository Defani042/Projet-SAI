#ifndef _LOG_C_
#define _LOG_C_
 
#include"log/log.h"

static FILE *log_file = NULL;

/*
R: création des dossier de log
E: rien
S: rien
A: Adrien
*/
void creer_dossiers_log()
{
    if (mkdir("fich", 0777) == -1 && errno != EEXIST)
    {
        perror("mkdir fich");
    }

    if (mkdir("fich/log", 0777) == -1 && errno != EEXIST)
    {
        perror("mkdir fich/log");
    }
}

/*
R: création des dossier de log
E: rien
S: 1 si ok sinon 0
A: Adrien
*/
int creer_fichier_log()
{
    FILE *f;

    /* Crée les dossiers avant le fichier */
    creer_dossiers_log();

    /* "a" = append : crée le fichier s'il n'existe pas */
    f = fopen(LOG_FILE_PATH, "a");
    if (f == NULL)
    {
        fprintf(stderr, "Erreur création fichier log (%s)\n", LOG_FILE_PATH);
        return 0;
    }

    fclose(f);
    return 1;
}

/*
R: création des dossier et des fichier log et init de log_file
E: rien
S: rien
A: Adrien
*/
void log_init()
{
    /* Assure que le fichier existe */
    if (!creer_fichier_log())
        return;

    log_file = fopen(LOG_FILE_PATH, "a");
    if (!log_file)
    {
        fprintf(stderr, LOG ERR"ouverture fichier log (%s)\n", LOG_FILE_PATH);
        exit(EXIT_FAILURE);
    }
}


/*
R: écriture dans les fichier de log
E: une chaine de caractere
S: rien
A: Adrien
*/
void log_message(const char *msg)
{
    if (!log_file)
        return;

    fprintf(log_file, "%s\n", msg);
    fflush(log_file); /* écrit immédiatement */
}

/*
R: fermeture du fichier
E: rien
S: rien
A: Adrien
*/
void log_close()
{
    if (log_file)
    {
        log_message(LOG SUCC "fermeuture des logs !");
        fclose(log_file);
        log_file = NULL;
    }
}

/*
R: netoyer les fichier de log
E: rien
S: rien
A: Adrien
*/
int log_nettoyer()
{
    if (!log_file)
        return 0;

    /* Ferme le fichier pour pouvoir le rouvrir en mode écriture */
    fclose(log_file);

    /* Ouvre en "w" pour écraser le contenu */
    log_file = fopen(LOG_FILE_PATH, "w");
    if (!log_file)
    {
        fprintf(stderr, "Erreur nettoyage fichier log (%s)\n", LOG_FILE_PATH);
        return 0;
    }
    log_message(LOG SUCC "netoyage des logs des logs !");
    /* Remet le fichier en mode append pour les prochaines écritures */
    fclose(log_file);
    log_file = fopen(LOG_FILE_PATH, "a");
    if (!log_file)
    {
        fprintf(stderr, "Erreur réouverture fichier log (%s)\n", LOG_FILE_PATH);
        return 0;
    }
    log_message(LOG SUCC "ouverture  des logs !");

    return 1;
}
#endif /*_LOG_C_*/