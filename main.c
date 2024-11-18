#include <stdio.h>
#include "map.h"
#include "arbre.h"
#include "chemin.h"


int main() {
    srand(time(NULL));
    t_map map;

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);



    t_localisation position_actuel = {5, 4, 0}; // (x, y, orientation)

    // Créer la racine de l'arbre
    Node* arbre = create_node(position_actuel, 0);

    // Struct pour stocker le chemin minimal
    CheminMin chemin_min;
    chemin_min.valeur_min = 10000; // Valeur initiale haute pour la comparaison
    chemin_min.profondeur = 0;

    // Appel de la fonction arbre_complet ou arbre_recurcif
    // Utilisation de `arbre_complet`
    //arbre_recurcif(arbre, 5, position_actuel, map, &chemin_min);
    arbre_complet(arbre, position_actuel, map, &chemin_min);
    printf(" la feuille avec le meilleur cout est à %d \n", chemin_min.valeur_min);
    // Affichage de l'arbre complet
    afficher_arbre(arbre);

    return 0;
}

