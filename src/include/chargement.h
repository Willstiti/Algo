#ifndef CHARGEMENT_H
#define CHARGEMENT_H

#include "collection.h"

#define CHARGEMENT_CASES_MAX 25000000   /* taille max du tableau de calcul (100 Mo) */

typedef struct {
    int *choisi;          /* choisi[i] = 1 si c->colis[i] est charge, NULL si aucun chargement */
    int nb_colis;         /* nombre de colis au moment du calcul */
    int capacite;         /* kg */
    int avec_priorite;    /* 0 : valeur maximale, 1 : score avec priorite */
    int gain;             /* valeur totale ou score total */
} Chargement;

/* Choisit les colis qui donnent la plus grande valeur totale sans depasser
 * la capacite (programmation dynamique). Remplit choisi, retourne la valeur
 * totale ou -1 en cas d'erreur. O(n x cap) en temps et en memoire */
int chargement_optimal(const CollectionColis *c, int capacite, int *choisi);

/* Score d'un colis : valeur x (9 - priorite). O(1) */
int score_priorite(const Colis *colis);

/* Comme chargement_optimal, mais maximise le score total. O(n x cap) */
int chargement_priorite(const CollectionColis *c, int capacite, int *choisi);

/* Calcule un chargement et le range dans ch. Retourne 1 si reussi, 0 sinon */
int chargement_preparer(const CollectionColis *c, int capacite,
                        int avec_priorite, Chargement *ch);

void chargement_afficher(const CollectionColis *c, const Chargement *ch);
void chargement_liberer(Chargement *ch);

#endif
