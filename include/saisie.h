#ifndef SAISIE_H
#define SAISIE_H

/* Affiche "message" et redemande tant que l'utilisateur ne tape pas un
 * entier. Quitte le programme si l'entree est fermee (Ctrl+D). */
int lire_entier(const char *message);

/* Affiche "message" et lit une ligne de texte (sans le retour a la ligne) */
void lire_texte(const char *message, char *buf, int taille);

#endif
