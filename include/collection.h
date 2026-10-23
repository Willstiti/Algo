#ifndef COLLECTION_H
#define COLLECTION_H

#include "colis.h"

/* L'ensemble des colis.
 *
 * - colis : tableau dynamique. Quand il est plein, sa capacite double,
 *   ce qui rend l'ajout O(1) amorti (recopies totales < 2n).
 *
 * - index : table de hachage id -> position dans le tableau colis.
 *   Chaque case contient une position ou -1 (case vide). Les collisions
 *   sont gerees en essayant la case suivante (sondage lineaire).
 *   La table reste remplie a 50 % au plus : recherche en O(1) en moyenne,
 *   au lieu de O(n) en parcourant le tableau.
 */
typedef struct {
    Colis *colis;
    int taille;           /* nombre de colis */
    int capacite;         /* places dans le tableau colis */

    int *index;
    int taille_index;     /* nombre de cases, toujours une puissance de 2 */
} CollectionColis;

/* Resultat de collection_ajouter */
typedef enum {
    AJOUT_OK,
    AJOUT_INVALIDE,       /* donnees incorrectes */
    AJOUT_DOUBLON         /* id deja utilise */
} ResultatAjout;

void collection_init(CollectionColis *c);       /* O(1) */
void collection_liberer(CollectionColis *c);    /* O(1) */

/* Etape 1 : ajouter un colis. O(1) amorti */
ResultatAjout collection_ajouter(CollectionColis *c, int id, int poids,
                                 int valeur, int priorite, const char *destination);

/* Etape 1 : afficher les colis dans l'ordre d'ajout (au plus "limite"). O(n) */
void collection_afficher(const CollectionColis *c, int limite);

/* Etape 2 : retrouver un colis par son id. NULL s'il n'existe pas.
 * O(1) en moyenne */
const Colis *collection_rechercher(const CollectionColis *c, int id);

/* Etape 2 : recherche puis affiche le colis, ou "introuvable". O(1) en moyenne */
void collection_afficher_recherche(const CollectionColis *c, int id);

/* Texte correspondant au resultat d'un ajout ("ajoute", "refuse : ..."). O(1) */
const char *resultat_ajout_texte(ResultatAjout r);

/* Plus grand id present, ou -1 si la collection est vide. O(n) */
int collection_id_max(const CollectionColis *c);

/* Affiche les statistiques : nombre de colis, poids et valeur totaux
 * et moyens, poids min / max, repartition par priorite. O(n) */
void collection_afficher_statistiques(const CollectionColis *c);

#endif
