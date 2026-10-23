#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "performance.h"
#include "collection.h"
#include "tri.h"
#include "generation.h"
#include "chargement.h"

#define NB_RECHERCHES 10000

static double ms_depuis(clock_t debut)
{
    return 1000.0 * (double)(clock() - debut) / CLOCKS_PER_SEC;
}

/* Recherche par parcours, O(n) : uniquement pour comparer avec le hachage */
static const Colis *rechercher_lineaire(const CollectionColis *c, int id)
{
    for (int i = 0; i < c->taille; i++)
        if (c->colis[i].id == id)
            return &c->colis[i];
    return NULL;
}

void mesurer_performances(void)
{
    int tailles[] = {100, 1000, 10000, 100000};

    printf("%-9s %-10s %-14s %-16s %-11s %-11s %-11s\n", "n", "ajout n",
           "10000 rech.", "10000 rech.", "tri poids", "tri valeur", "tri prio");
    printf("%-9s %-10s %-14s %-16s\n", "", "", "(hachage)", "(parcours)");

    for (int k = 0; k < 4; k++) {
        int n = tailles[k];
        CollectionColis c;
        collection_init(&c);

        clock_t debut = clock();
        generer_colis(&c, 0, n);
        double t_ajout = ms_depuis(debut);

        /* on compte les resultats, sinon le compilateur supprime la boucle */
        int trouves = 0;
        debut = clock();
        for (int i = 0; i < NB_RECHERCHES; i++)
            if (collection_rechercher(&c, rand() % n) != NULL)
                trouves++;
        double t_recherche = ms_depuis(debut);

        debut = clock();
        for (int i = 0; i < NB_RECHERCHES; i++)
            if (rechercher_lineaire(&c, rand() % n) != NULL)
                trouves++;
        double t_lineaire = ms_depuis(debut);

        if (trouves != 2 * NB_RECHERCHES)
            printf("Attention : %d recherches sans resultat\n", 2 * NB_RECHERCHES - trouves);

        debut = clock();
        free(collection_trier_par_poids(&c));
        double t_poids = ms_depuis(debut);

        debut = clock();
        free(collection_trier_par_valeur(&c));
        double t_valeur = ms_depuis(debut);

        debut = clock();
        free(collection_trier_par_priorite(&c));
        double t_priorite = ms_depuis(debut);

        printf("%-9d %-10.2f %-14.2f %-16.2f %-11.2f %-11.2f %-11.2f\n",
               n, t_ajout, t_recherche, t_lineaire, t_poids, t_valeur, t_priorite);
        collection_liberer(&c);
    }
    printf("(temps en millisecondes)\n");

    printf("\nChargement optimal (etape 4)\n");
    printf("%-9s %-9s %-12s %-10s\n", "n", "cap (kg)", "n x cap", "temps (ms)");

    int essais[][2] = {         /* {nombre de colis, capacite} */
        {1000, 500}, {2000, 500}, {4000, 500},
        {1000, 1000}, {1000, 2000},
        {100000, 50}
    };
    for (int k = 0; k < 6; k++) {
        int n = essais[k][0];
        int capacite = essais[k][1];
        CollectionColis c;
        collection_init(&c);
        generer_colis(&c, 0, n);

        int *choisi = malloc(n * sizeof(int));
        if (choisi == NULL) {
            fprintf(stderr, "Erreur : memoire insuffisante.\n");
            exit(EXIT_FAILURE);
        }

        clock_t debut = clock();
        chargement_optimal(&c, capacite, choisi);
        double t = ms_depuis(debut);

        printf("%-9d %-9d %-12ld %-10.2f\n", n, capacite, (long)n * capacite, t);
        free(choisi);
        collection_liberer(&c);
    }
}
