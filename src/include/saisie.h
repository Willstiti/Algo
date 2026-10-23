#ifndef SAISIE_H
#define SAISIE_H

/* Redemande tant que l'utilisateur ne tape pas un entier */
int lire_entier(const char *message);

/* Lit une ligne de texte sans le '\n' */
void lire_texte(const char *message, char *buf, int taille);

#endif
