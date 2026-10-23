#include <stdlib.h>
#include "generation.h"

void generer_colis(CollectionColis *c, int premier_id, int n)
{
    static const char *villes[] = {
        "Paris", "Lille", "Lyon", "Marseille", "Nantes", "Bordeaux"
    };

    for (int i = 0; i < n; i++)
        collection_ajouter(c, premier_id + i,
                           1 + rand() % 50,      /* poids : 1 a 50 */
                           1 + rand() % 100,     /* valeur : 1 a 100 */
                           1 + rand() % 5,       /* priorite : 1 a 5 */
                           villes[rand() % 6]);
}
