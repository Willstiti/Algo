#include <stdio.h>
#include <string.h>
#include "colis.h"

int colis_creer(Colis *c, int id, int poids, int valeur,
                int priorite, const char *destination)
{
    if (id < 0 || poids <= 0 || valeur < 0 || priorite < 1 || priorite > 5
        || destination == NULL || destination[0] == '\0')
        return 0;

    c->id = id;
    c->poids = poids;
    c->valeur = valeur;
    c->priorite = priorite;

    /* strncpy n'ajoute pas toujours le '\0' final */
    strncpy(c->destination, destination, TAILLE_DEST - 1);
    c->destination[TAILLE_DEST - 1] = '\0';
    return 1;
}

void colis_afficher_entete(void)
{
    printf("%-8s %-8s %-8s %-9s %s\n", "ID", "Poids", "Valeur", "Priorite", "Destination");
}

void colis_afficher(const Colis *c)
{
    printf("%-8d %-8d %-8d %-9d %s\n",
           c->id, c->poids, c->valeur, c->priorite, c->destination);
}
