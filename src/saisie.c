/* On lit une ligne entiere puis on la convertit : une saisie incorrecte
 * ne bloque pas le programme (contrairement a scanf) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "saisie.h"

int lire_entier(const char *message)
{
    char buf[64];
    char *fin;

    for (;;) {
        printf("%s", message);
        if (fgets(buf, sizeof buf, stdin) == NULL)
            exit(EXIT_SUCCESS);                     /* Ctrl+D */

        long v = strtol(buf, &fin, 10);
        if (fin != buf && (*fin == '\n' || *fin == '\0'))
            return (int)v;
        printf("Veuillez entrer un nombre entier.\n");
    }
}

void lire_texte(const char *message, char *buf, int taille)
{
    printf("%s", message);
    if (fgets(buf, taille, stdin) == NULL)
        exit(EXIT_SUCCESS);
    buf[strcspn(buf, "\n")] = '\0';                 /* retire le '\n' */
}
