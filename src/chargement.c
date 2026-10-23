/* Chargement du camion : programmation dynamique (sac a dos 0/1).
 * table[i][x] = meilleur gain avec les i premiers colis et x kg.
 * Le tableau 2D est range a plat : la case [i][x] est a i * (cap + 1) + x. */
#include <stdio.h>
#include <stdlib.h>
#include "chargement.h"

#define LIMITE_AFFICHAGE 50

int score_priorite(const Colis *colis)
{
    return colis->valeur * (9 - colis->priorite);
}

/* Gain d'un colis : sa valeur, ou son score si avec_priorite */
static int sac_a_dos(const CollectionColis *c, int capacite, int avec_priorite, int *choisi)
{
    int n = c->taille;
    int largeur = capacite + 1;

    if (capacite < 0)
        return -1;
    if ((double)(n + 1) * largeur > CHARGEMENT_CASES_MAX)
        return -1;

    int *table = malloc((n + 1) * largeur * sizeof(int));
    if (table == NULL)
        return -1;

    /* aucun colis : gain 0 */
    for (int x = 0; x <= capacite; x++)
        table[x] = 0;

    for (int i = 1; i <= n; i++) {
        const Colis *colis = &c->colis[i - 1];
        int p = colis->poids;
        int g;
        if (avec_priorite)
            g = score_priorite(colis);
        else
            g = colis->valeur;

        for (int x = 0; x <= capacite; x++) {
            int sans = table[(i - 1) * largeur + x];                    /* on ne le prend pas */
            int meilleur = sans;
            if (p <= x) {
                int avec = table[(i - 1) * largeur + (x - p)] + g;      /* on le prend */
                if (avec > sans)
                    meilleur = avec;
            }
            table[i * largeur + x] = meilleur;
        }
    }

    int gain_max = table[n * largeur + capacite];

    /* on remonte le tableau : si la valeur change entre deux lignes,
     * le colis a ete pris */
    int x = capacite;
    for (int i = n; i >= 1; i--) {
        if (table[i * largeur + x] != table[(i - 1) * largeur + x]) {
            choisi[i - 1] = 1;
            x -= c->colis[i - 1].poids;
        } else {
            choisi[i - 1] = 0;
        }
    }

    free(table);
    return gain_max;
}

int chargement_optimal(const CollectionColis *c, int capacite, int *choisi)
{
    return sac_a_dos(c, capacite, 0, choisi);
}

int chargement_priorite(const CollectionColis *c, int capacite, int *choisi)
{
    return sac_a_dos(c, capacite, 1, choisi);
}

int chargement_preparer(const CollectionColis *c, int capacite,
                        int avec_priorite, Chargement *ch)
{
    chargement_liberer(ch);

    int *choisi = malloc((c->taille + 1) * sizeof(int));
    if (choisi == NULL) {
        fprintf(stderr, "Erreur : memoire insuffisante.\n");
        exit(EXIT_FAILURE);
    }

    int gain = sac_a_dos(c, capacite, avec_priorite, choisi);
    if (gain < 0) {
        free(choisi);
        return 0;
    }

    ch->choisi = choisi;
    ch->nb_colis = c->taille;
    ch->capacite = capacite;
    ch->avec_priorite = avec_priorite;
    ch->gain = gain;
    return 1;
}

void chargement_afficher(const CollectionColis *c, const Chargement *ch)
{
    if (ch->choisi == NULL) {
        printf("Aucun chargement prepare.\n");
        return;
    }

    printf("Camion de %d kg, %s\n", ch->capacite,
           ch->avec_priorite ? "avec priorite (score)" : "valeur maximale");
    if (ch->nb_colis != c->taille)
        printf("Attention : des colis ont ete ajoutes depuis, preparez a nouveau le camion.\n");

    int poids_total = 0, valeur_totale = 0, nb = 0;
    colis_afficher_entete();
    for (int i = 0; i < ch->nb_colis; i++) {
        if (ch->choisi[i]) {
            if (nb < LIMITE_AFFICHAGE)
                colis_afficher(&c->colis[i]);
            poids_total += c->colis[i].poids;
            valeur_totale += c->colis[i].valeur;
            nb++;
        }
    }
    if (nb == 0)
        printf("(aucun colis ne rentre)\n");
    else if (nb > LIMITE_AFFICHAGE)
        printf("... (%d colis non affiches)\n", nb - LIMITE_AFFICHAGE);

    printf("-> %d colis charges, poids total %d / %d kg, valeur totale %d",
           nb, poids_total, ch->capacite, valeur_totale);
    if (ch->avec_priorite)
        printf(", score %d", ch->gain);
    printf("\n");
}

void chargement_liberer(Chargement *ch)
{
    free(ch->choisi);
    ch->choisi = NULL;
    ch->nb_colis = ch->capacite = ch->avec_priorite = ch->gain = 0;
}
