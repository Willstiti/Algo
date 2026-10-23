#include <stdio.h>
#include <stdlib.h>
#include "collection.h"

#define CAPACITE_INITIALE 16
#define CASE_VIDE -1

/* Case de depart d'un id dans l'index */
static int hacher(int id, int taille_index)
{
    return id % taille_index;
}

/* Range la position pos dans la premiere case libre a partir de hacher(id) */
static void index_inserer(CollectionColis *c, int pos)
{
    int i = hacher(c->colis[pos].id, c->taille_index);
    while (c->index[i] != CASE_VIDE)
        i = (i + 1) % c->taille_index;
    c->index[i] = pos;
}

/* Recree un index de "taille" cases et y replace tous les colis. O(n) */
static void index_reconstruire(CollectionColis *c, int taille)
{
    free(c->index);
    c->taille_index = taille;
    c->index = malloc(taille * sizeof(int));
    if (c->index == NULL) {
        fprintf(stderr, "Erreur : memoire insuffisante.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < taille; i++)
        c->index[i] = CASE_VIDE;
    for (int pos = 0; pos < c->taille; pos++)
        index_inserer(c, pos);
}

void collection_init(CollectionColis *c)
{
    c->taille = 0;
    c->capacite = CAPACITE_INITIALE;
    c->colis = malloc(c->capacite * sizeof(Colis));
    if (c->colis == NULL) {
        fprintf(stderr, "Erreur : memoire insuffisante.\n");
        exit(EXIT_FAILURE);
    }
    c->taille_index = 2 * CAPACITE_INITIALE;
    c->index = malloc(c->taille_index * sizeof(int));
    if (c->index == NULL) {
        fprintf(stderr, "Erreur : memoire insuffisante.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < c->taille_index; i++)
        c->index[i] = CASE_VIDE;
}

void collection_liberer(CollectionColis *c)
{
    free(c->colis);
    free(c->index);
    c->colis = NULL;
    c->index = NULL;
    c->taille = c->capacite = c->taille_index = 0;
}

const Colis *collection_rechercher(const CollectionColis *c, int id)
{
    /* on avance jusqu'a trouver l'id ou une case vide (id absent) */
    int i = hacher(id, c->taille_index);
    while (c->index[i] != CASE_VIDE) {
        const Colis *p = &c->colis[c->index[i]];
        if (p->id == id)
            return p;
        i = (i + 1) % c->taille_index;
    }
    return NULL;
}

ResultatAjout collection_ajouter(CollectionColis *c, int id, int poids, int valeur, int priorite, const char *destination)
{
    Colis nouveau;
    if (!colis_creer(&nouveau, id, poids, valeur, priorite, destination))
        return AJOUT_INVALIDE;
    if (collection_rechercher(c, id) != NULL)
        return AJOUT_DOUBLON;

    /* tableau plein : on double sa capacite */
    if (c->taille == c->capacite) {
        c->capacite *= 2;
        c->colis = realloc(c->colis, c->capacite * sizeof(Colis));
        if (c->colis == NULL) {
            fprintf(stderr, "Erreur : memoire insuffisante.\n");
            exit(EXIT_FAILURE);
        }
    }

    c->colis[c->taille] = nouveau;
    c->taille++;

    /* index rempli a plus de 50 % : on double sa taille */
    if (2 * c->taille > c->taille_index)
        index_reconstruire(c, 2 * c->taille_index);
    else
        index_inserer(c, c->taille - 1);

    return AJOUT_OK;
}

void collection_afficher(const CollectionColis *c, int limite)
{
    colis_afficher_entete();
    for (int i = 0; i < c->taille && i < limite; i++)
        colis_afficher(&c->colis[i]);
    if (c->taille > limite)
        printf("... (%d colis non affiches)\n", c->taille - limite);
}

void collection_afficher_recherche(const CollectionColis *c, int id)
{
    const Colis *p = collection_rechercher(c, id);
    if (p == NULL) {
        printf("Colis %d introuvable.\n", id);
    } else {
        colis_afficher_entete();
        colis_afficher(p);
    }
}

const char *resultat_ajout_texte(ResultatAjout r)
{
    switch (r) {
    case AJOUT_OK:      return "ajoute";
    case AJOUT_DOUBLON: return "refuse : id deja utilise";
    default:            return "refuse : donnees invalides";
    }
}

int collection_id_max(const CollectionColis *c)
{
    int max = -1;
    for (int i = 0; i < c->taille; i++)
        if (c->colis[i].id > max)
            max = c->colis[i].id;
    return max;
}

void collection_afficher_statistiques(const CollectionColis *c)
{
    if (c->taille == 0) {
        printf("Aucun colis.\n");
        return;
    }

    long poids_total = 0, valeur_totale = 0;
    int poids_min = c->colis[0].poids, poids_max = c->colis[0].poids;
    int par_priorite[6] = {0};               /* cases 1 a 5 utilisees */

    for (int i = 0; i < c->taille; i++) {
        const Colis *p = &c->colis[i];
        poids_total += p->poids;
        valeur_totale += p->valeur;
        if (p->poids < poids_min) poids_min = p->poids;
        if (p->poids > poids_max) poids_max = p->poids;
        par_priorite[p->priorite]++;
    }

    printf("Nombre de colis : %d\n", c->taille);
    printf("Poids total     : %ld kg (moyenne %.1f kg, min %d, max %d)\n",
           poids_total, (double)poids_total / c->taille, poids_min, poids_max);
    printf("Valeur totale   : %ld (moyenne %.1f)\n",
           valeur_totale, (double)valeur_totale / c->taille);
    printf("Par priorite    :");
    for (int p = 1; p <= 5; p++)
        printf("  P%d = %d", p, par_priorite[p]);
    printf("\n");
}
