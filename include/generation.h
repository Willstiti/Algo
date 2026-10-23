#ifndef GENERATION_H
#define GENERATION_H

#include "collection.h"

/* Ajoute n colis fictifs (valeurs aleatoires) d'id premier_id a
 * premier_id + n - 1. Appeler srand() avant. O(n) amorti */
void generer_colis(CollectionColis *c, int premier_id, int n);

#endif
