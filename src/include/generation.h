#ifndef GENERATION_H
#define GENERATION_H

#include "collection.h"

/* Ajoute n colis aleatoires d'id premier_id, premier_id + 1, ... O(n) */
void generer_colis(CollectionColis *c, int premier_id, int n);

#endif
