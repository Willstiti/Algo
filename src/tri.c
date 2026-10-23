/* Tri fusion : on coupe en deux, on trie chaque moitie, on fusionne.
 * Une version par critere ; seule la comparaison dans la fusion change. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tri.h"

/* Copie des colis : on trie la copie pour ne pas deplacer les colis de
 * la collection (l'index garde des positions) */
static Colis *copier(const CollectionColis *c)
{
    Colis *t = malloc((c->taille + 1) * sizeof(Colis));
    if (t == NULL) {
        fprintf(stderr, "Erreur : memoire insuffisante.\n");
        exit(EXIT_FAILURE);
    }
    memcpy(t, c->colis, c->taille * sizeof(Colis));
    return t;
}

static void afficher_et_liberer(Colis *t, int n, int limite)
{
    colis_afficher_entete();
    for (int i = 0; i < n && i < limite; i++)
        colis_afficher(&t[i]);
    if (n > limite)
        printf("... (%d colis non affiches)\n", n - limite);
    free(t);
}

/* ---------------- Par poids (croissant) ---------------- */

/* Fusionne t[g..m] et t[m+1..d], deja tries */
static void fusion_poids(Colis *t, Colis *tmp, int g, int m, int d)
{
    int i = g, j = m + 1, k = g;
    while (i <= m && j <= d) {
        if (t[j].poids < t[i].poids)
            tmp[k++] = t[j++];
        else
            tmp[k++] = t[i++];
    }
    while (i <= m) tmp[k++] = t[i++];
    while (j <= d) tmp[k++] = t[j++];
    for (k = g; k <= d; k++)
        t[k] = tmp[k];
}

static void tri_fusion_poids(Colis *t, Colis *tmp, int g, int d)
{
    if (g >= d)
        return;
    int m = (g + d) / 2;
    tri_fusion_poids(t, tmp, g, m);
    tri_fusion_poids(t, tmp, m + 1, d);
    fusion_poids(t, tmp, g, m, d);
}

Colis *collection_trier_par_poids(const CollectionColis *c)
{
    Colis *t = copier(c);
    Colis *tmp = malloc((c->taille + 1) * sizeof(Colis));
    if (tmp == NULL) {
        fprintf(stderr, "Erreur : memoire insuffisante.\n");
        exit(EXIT_FAILURE);
    }
    tri_fusion_poids(t, tmp, 0, c->taille - 1);
    free(tmp);
    return t;
}

void collection_afficher_par_poids(const CollectionColis *c, int limite)
{
    afficher_et_liberer(collection_trier_par_poids(c), c->taille, limite);
}

/* ---------------- Par valeur (decroissante) ---------------- */

static void fusion_valeur(Colis *t, Colis *tmp, int g, int m, int d)
{
    int i = g, j = m + 1, k = g;
    while (i <= m && j <= d) {
        if (t[j].valeur > t[i].valeur)
            tmp[k++] = t[j++];
        else
            tmp[k++] = t[i++];
    }
    while (i <= m) tmp[k++] = t[i++];
    while (j <= d) tmp[k++] = t[j++];
    for (k = g; k <= d; k++)
        t[k] = tmp[k];
}

static void tri_fusion_valeur(Colis *t, Colis *tmp, int g, int d)
{
    if (g >= d)
        return;
    int m = (g + d) / 2;
    tri_fusion_valeur(t, tmp, g, m);
    tri_fusion_valeur(t, tmp, m + 1, d);
    fusion_valeur(t, tmp, g, m, d);
}

Colis *collection_trier_par_valeur(const CollectionColis *c)
{
    Colis *t = copier(c);
    Colis *tmp = malloc((c->taille + 1) * sizeof(Colis));
    if (tmp == NULL) {
        fprintf(stderr, "Erreur : memoire insuffisante.\n");
        exit(EXIT_FAILURE);
    }
    tri_fusion_valeur(t, tmp, 0, c->taille - 1);
    free(tmp);
    return t;
}

void collection_afficher_par_valeur(const CollectionColis *c, int limite)
{
    afficher_et_liberer(collection_trier_par_valeur(c), c->taille, limite);
}

/* ---------------- Par priorite (1 en premier) ---------------- */

static void fusion_priorite(Colis *t, Colis *tmp, int g, int m, int d)
{
    int i = g, j = m + 1, k = g;
    while (i <= m && j <= d) {
        if (t[j].priorite < t[i].priorite)
            tmp[k++] = t[j++];
        else
            tmp[k++] = t[i++];
    }
    while (i <= m) tmp[k++] = t[i++];
    while (j <= d) tmp[k++] = t[j++];
    for (k = g; k <= d; k++)
        t[k] = tmp[k];
}

static void tri_fusion_priorite(Colis *t, Colis *tmp, int g, int d)
{
    if (g >= d)
        return;
    int m = (g + d) / 2;
    tri_fusion_priorite(t, tmp, g, m);
    tri_fusion_priorite(t, tmp, m + 1, d);
    fusion_priorite(t, tmp, g, m, d);
}

Colis *collection_trier_par_priorite(const CollectionColis *c)
{
    Colis *t = copier(c);
    Colis *tmp = malloc((c->taille + 1) * sizeof(Colis));
    if (tmp == NULL) {
        fprintf(stderr, "Erreur : memoire insuffisante.\n");
        exit(EXIT_FAILURE);
    }
    tri_fusion_priorite(t, tmp, 0, c->taille - 1);
    free(tmp);
    return t;
}

void collection_afficher_par_priorite(const CollectionColis *c, int limite)
{
    afficher_et_liberer(collection_trier_par_priorite(c), c->taille, limite);
}
