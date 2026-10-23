#ifndef TRI_H
#define TRI_H

#include "colis.h"
#include "collection.h"

/* Retournent une copie triee des colis (tri fusion), a liberer avec free().
 * O(n log n) */
Colis *collection_trier_par_poids(const CollectionColis *c);      /* poids croissant */
Colis *collection_trier_par_valeur(const CollectionColis *c);     /* valeur decroissante */
Colis *collection_trier_par_priorite(const CollectionColis *c);   /* priorite 1 en premier */

/* Trient puis affichent au plus "limite" colis. O(n log n) */
void collection_afficher_par_poids(const CollectionColis *c, int limite);
void collection_afficher_par_valeur(const CollectionColis *c, int limite);
void collection_afficher_par_priorite(const CollectionColis *c, int limite);

#endif
