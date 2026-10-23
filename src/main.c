#include <stdlib.h>
#include <time.h>
#include "collection.h"
#include "menu.h"

int main(void)
{
    CollectionColis c;
    collection_init(&c);
    srand((unsigned int)time(NULL));

    /* colis de l'enonce */
    collection_ajouter(&c, 101, 8, 20, 2, "Paris");
    collection_ajouter(&c, 102, 3, 10, 5, "Lille");
    collection_ajouter(&c, 103, 12, 40, 1, "Lyon");
    collection_ajouter(&c, 104, 5, 25, 4, "Paris");
    collection_ajouter(&c, 105, 2, 15, 3, "Lille");

    menu_lancer(&c);

    collection_liberer(&c);
    return 0;
}
