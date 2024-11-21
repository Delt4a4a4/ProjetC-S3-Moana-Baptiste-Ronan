#include <stdio.h>
#include "map.h"
#include "arbre.h"
#include "chemin.h"


int main() {
    srand(time(NULL));
    t_map map, mapcree;
    t_queue file = createQueue(100);
    t_stack stack_x = createStack(100);
    t_stack stack_y = createStack(100);

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

    int largeur = 5;
    int hauteur = 5;

    // Appel de la fonction pour générer et écrire la carte
    créer_carte(largeur, hauteur);
    mapcree =createMapFromFile("..\\maps\\fonction_creation_map.map");
    display_arbre(mapcree);

    // Utilisation de `arbre_complet`
    printf("Début ");
    arbre_complet(arbre, position_actuel, map, &chemin_min);

    // Affichage de l'arbre complet
    afficher_arbre(arbre);
    for (int i = 0; i<=chemin_min.profondeur; i++){
        printf("\nvaleurs n°%d x = %d y = %d",i ,chemin_min.nodes[i]->pos.pos.x,chemin_min.nodes[i]->pos.pos.y);
        push(&stack_x, chemin_min.nodes[i]->pos.pos.x);
        push(&stack_y, chemin_min.nodes[i]->pos.pos.y);
    }

    // localisation initial en dure ou aleatoire
    //int x = rand() % 7 ou hauteur;
    //int y = rand() % 6 ou largeur;
    //int ori = rand() % 4;

    loc_init(position_actuel.pos.x,position_actuel.pos.y,position_actuel.ori);
    while (chemin_min.valeur_min != 0 ){
        position_actuel.pos.x = chemin_min.nodes[chemin_min.profondeur]->pos.pos.x;
        position_actuel.pos.y = chemin_min.nodes[chemin_min.profondeur]->pos.pos.y;
        position_actuel.ori = chemin_min.nodes[chemin_min.profondeur]->pos.ori;
        Node* arbre = create_node(position_actuel, 0);
        arbre_complet(arbre, position_actuel, map, &chemin_min);
        for (int i = 1; i<=chemin_min.profondeur; i++){
            printf("valeurs n°%d x = %d y = %d\n",i ,chemin_min.nodes[i]->pos.pos.x,chemin_min.nodes[i]->pos.pos.y);
            push(&stack_x, chemin_min.nodes[i]->pos.pos.x);
            push(&stack_y, chemin_min.nodes[i]->pos.pos.y);
        }
        afficher_arbre(arbre);
        chemin_effetue(chemin_min,file);



    }
    afficher_chemin(stack_x,stack_y);
    printf("Termine !");
    return 0;
}

