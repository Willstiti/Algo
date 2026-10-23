#ifndef COLIS_H
#define COLIS_H

#define TAILLE_DEST 32   /* longueur max de la destination, '\0' compris */

typedef struct {
    int id;
    int poids;
    int valeur;
    int priorite;        /* 1 (le plus urgent) a 5 (le moins urgent) */
    char destination[TAILLE_DEST];
} Colis;

/* Remplit c si les donnees sont valides. Retourne 1 si valide, 0 sinon. O(1) */
int colis_creer(Colis *c, int id, int poids, int valeur,
                int priorite, const char *destination);

void colis_afficher_entete(void);
void colis_afficher(const Colis *c);

#endif
