#ifndef COLLECTION_H
#define COLLECTION_H

#include "colis.h"

typedef struct {
    Colis *colis;         /* tableau dynamique (capacite doublee quand il est plein) */
    int taille;           /* nombre de colis */
    int capacite;         /* places dans le tableau colis */

    int *index;           /* table de hachage : id -> position dans colis, -1 si vide */
    int taille_index;     /* nombre de cases de l'index */
} CollectionColis;

typedef enum {
    AJOUT_OK,
    AJOUT_INVALIDE,       /* donnees incorrectes */
    AJOUT_DOUBLON         /* id deja utilise */
} ResultatAjout;

void collection_init(CollectionColis *c);
void collection_liberer(CollectionColis *c);

/* Ajoute un colis. O(1) amorti */
ResultatAjout collection_ajouter(CollectionColis *c, int id, int poids,
                                 int valeur, int priorite, const char *destination);

/* Affiche les colis dans l'ordre d'ajout (au plus "limite"). O(n) */
void collection_afficher(const CollectionColis *c, int limite);

/* Retourne le colis d'identifiant id, ou NULL. Meilleur cas O(1), pire cas O(n) */
const Colis *collection_rechercher(const CollectionColis *c, int id);

/* Recherche puis affiche le colis, ou "introuvable" */
void collection_afficher_recherche(const CollectionColis *c, int id);

/* Message correspondant au resultat d'un ajout */
const char *resultat_ajout_texte(ResultatAjout r);

/* Plus grand id, ou -1 si la collection est vide. O(n) */
int collection_id_max(const CollectionColis *c);

/* Nombre de colis, poids et valeur totaux, repartition par priorite. O(n) */
void collection_afficher_statistiques(const CollectionColis *c);

#endif
