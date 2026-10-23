#ifndef CHARGEMENT_H
#define CHARGEMENT_H

#include "collection.h"

/* Taille max du tableau de calcul (nombre de cases) : au-dela, la
 * memoire necessaire serait trop grande (25 millions d'int = 100 Mo). */
#define CHARGEMENT_CASES_MAX 25000000

/* Un chargement de camion prepare */
typedef struct {
    int *choisi;          /* choisi[i] = 1 si c->colis[i] est charge, NULL si aucun */
    int nb_colis;         /* nombre de colis dans la collection au moment du calcul */
    int capacite;         /* capacite du camion (kg) */
    int avec_priorite;    /* 0 : valeur maximale, 1 : score avec priorite */
    int gain;             /* valeur totale ou score total obtenu */
} Chargement;

/* Etape 4 : choisit les colis a charger dans un camion de "capacite" kg
 * pour obtenir la plus grande valeur totale possible (probleme du sac
 * a dos 0/1), par programmation dynamique. La solution est OPTIMALE.
 *
 * choisi : tableau de c->taille cases fourni par l'appelant.
 *          En sortie, choisi[i] = 1 si c->colis[i] est charge, 0 sinon.
 * Retourne la valeur totale chargee, ou -1 si la capacite est negative
 * ou si le calcul demande trop de memoire.
 *
 * Temps O(n x W), espace O(n x W)   (n = nombre de colis, W = capacite) */
int chargement_optimal(const CollectionColis *c, int capacite, int *choisi);

/* Etape 5 : score d'un colis = valeur x (9 - priorite).
 * Priorite 1 -> x8, 2 -> x7, 3 -> x6, 4 -> x5, 5 -> x4. O(1) */
int score_priorite(const Colis *colis);

/* Etape 5 : meme calcul que chargement_optimal, mais on maximise le
 * score total (valeur + priorite) au lieu de la valeur seule.
 * Le poids reste une contrainte : poids total <= capacite.
 * Retourne le score total, ou -1 en cas d'erreur.
 * Temps O(n x W), espace O(n x W) */
int chargement_priorite(const CollectionColis *c, int capacite, int *choisi);

/* Prepare un chargement (avec ou sans priorite) et le range dans *ch.
 * Libere d'abord l'ancien chargement contenu dans *ch.
 * Retourne 1 si le calcul a reussi, 0 sinon. */
int chargement_preparer(const CollectionColis *c, int capacite,
                        int avec_priorite, Chargement *ch);

/* Affiche un chargement prepare : colis charges, poids, valeur, score */
void chargement_afficher(const CollectionColis *c, const Chargement *ch);

/* Libere la memoire d'un chargement (le remet a "aucun chargement") */
void chargement_liberer(Chargement *ch);

#endif
