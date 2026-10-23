#ifndef PERFORMANCE_H
#define PERFORMANCE_H

/* Pour 100, 1 000, 10 000 et 100 000 colis fictifs, mesure et affiche
 * le temps des etapes 1 (ajout), 2 (10 000 recherches) et 3 (tris).
 * Permet de verifier les complexites : ajout et recherche O(1),
 * tri O(n log n). */
void mesurer_performances(void);

#endif
