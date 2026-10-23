#ifndef COLIS_H
#define COLIS_H

#define TAILLE_DEST 32   /* longueur max de la destination, '\0' compris */

/* Un colis. Taille fixe : se range directement dans un tableau. */
typedef struct {
    int id;
    int poids;
    int valeur;
    int priorite;                    /* 1 (le plus urgent) a 5 (le moins urgent) */
    char destination[TAILLE_DEST];
} Colis;

/* Remplit *c apres verification des donnees.
 * Retourne 1 si le colis est valide, 0 sinon (c n'est pas modifie). O(1) */
int colis_creer(Colis *c, int id, int poids, int valeur,
                int priorite, const char *destination);

/* Affiche la ligne de titre, puis un colis par ligne. O(1) */
void colis_afficher_entete(void);
void colis_afficher(const Colis *c);

#endif
