#include <stdio.h>
#include "menu.h"
#include "collection.h"
#include "tri.h"
#include "chargement.h"
#include "generation.h"
#include "performance.h"
#include "saisie.h"

#define LIMITE 50   /* nombre max de lignes affichees */

static void menu_ajouter(CollectionColis *c)
{
    char dest[TAILLE_DEST];
    int id = lire_entier("Identifiant : ");
    int poids = lire_entier("Poids (kg) : ");
    int valeur = lire_entier("Valeur : ");
    int priorite = lire_entier("Priorite (1 = tres urgent ... 5 = peu urgent) : ");
    lire_texte("Destination : ", dest, sizeof dest);

    ResultatAjout r = collection_ajouter(c, id, poids, valeur, priorite, dest);
    printf("Colis %d %s.\n", id, resultat_ajout_texte(r));
}

static void menu_organiser(const CollectionColis *c)
{
    printf("1. Par poids (croissant)\n");
    printf("2. Par valeur (decroissante)\n");
    printf("3. Par priorite (1 en premier)\n");
    int choix = lire_entier("Critere : ");

    if (choix == 1)
        collection_afficher_par_poids(c, LIMITE);
    else if (choix == 2)
        collection_afficher_par_valeur(c, LIMITE);
    else if (choix == 3)
        collection_afficher_par_priorite(c, LIMITE);
    else
        printf("Choix invalide.\n");
}

static void menu_preparer(const CollectionColis *c, Chargement *ch)
{
    int capacite = lire_entier("Capacite du camion (kg) : ");
    printf("1. Valeur totale maximale\n");
    printf("2. Avec priorite (score = valeur x (9 - priorite))\n");
    int mode = lire_entier("Mode : ");
    if (mode != 1 && mode != 2) {
        printf("Choix invalide.\n");
        return;
    }

    if (chargement_preparer(c, capacite, mode == 2, ch))
        chargement_afficher(c, ch);
    else
        printf("Calcul impossible (capacite negative ou trop de memoire necessaire).\n");
}

static void menu_generer(CollectionColis *c)
{
    int n = lire_entier("Nombre de colis a generer : ");
    if (n <= 0) {
        printf("Rien a faire.\n");
        return;
    }
    generer_colis(c, collection_id_max(c) + 1, n);
    printf("%d colis generes (%d au total).\n", n, c->taille);
}

/* Remplace la collection par un jeu de l'enonce */
static void menu_exemple(CollectionColis *c, Chargement *ch)
{
    printf("1. Colis 101 a 105 (gestion des colis)\n");
    printf("2. Colis A, B, C, D (camion et priorites)\n");
    int choix = lire_entier("Jeu : ");
    if (choix != 1 && choix != 2) {
        printf("Choix invalide.\n");
        return;
    }

    chargement_liberer(ch);
    collection_liberer(c);
    collection_init(c);

    if (choix == 1) {
        collection_ajouter(c, 101, 8, 20, 2, "Paris");
        collection_ajouter(c, 102, 3, 10, 5, "Lille");
        collection_ajouter(c, 103, 12, 40, 1, "Lyon");
        collection_ajouter(c, 104, 5, 25, 4, "Paris");
        collection_ajouter(c, 105, 2, 15, 3, "Lille");
    } else {
        /* A, B, C, D */
        collection_ajouter(c, 1, 8, 20, 5, "A");
        collection_ajouter(c, 2, 6, 25, 1, "B");
        collection_ajouter(c, 3, 5, 18, 4, "C");
        collection_ajouter(c, 4, 4, 14, 3, "D");
    }
    printf("%d colis charges.\n", c->taille);
}

void menu_lancer(CollectionColis *c)
{
    Chargement ch = {NULL, 0, 0, 0, 0};

    for (;;) {
        printf("\n===== GESTION DES LIVRAISONS ===== (%d colis)\n", c->taille);
        printf("1. Afficher les colis\n");
        printf("2. Ajouter un colis\n");
        printf("3. Rechercher un colis\n");
        printf("4. Organiser les colis\n");
        printf("5. Preparer un camion\n");
        printf("6. Afficher le chargement\n");
        printf("7. Afficher les statistiques\n");
        printf("8. Generer des colis aleatoires\n");
        printf("9. Charger un jeu d'exemple\n");
        printf("10. Mesurer les performances\n");
        printf("0. Quitter\n");
        int choix = lire_entier("Choix : ");
        printf("\n");

        switch (choix) {
        case 1:  collection_afficher(c, LIMITE); break;
        case 2:  menu_ajouter(c); break;
        case 3:  collection_afficher_recherche(c, lire_entier("Identifiant : ")); break;
        case 4:  menu_organiser(c); break;
        case 5:  menu_preparer(c, &ch); break;
        case 6:  chargement_afficher(c, &ch); break;
        case 7:  collection_afficher_statistiques(c); break;
        case 8:  menu_generer(c); break;
        case 9:  menu_exemple(c, &ch); break;
        case 10: mesurer_performances(); break;
        case 0:  chargement_liberer(&ch); return;
        default: printf("Choix invalide.\n");
        }
    }
}
