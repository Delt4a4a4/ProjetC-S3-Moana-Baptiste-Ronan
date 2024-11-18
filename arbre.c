//
// Created by rwong on 29/10/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

#define max_mouv 5
#define nb_enfant_max 4

int avant_10 = 22;
int avant_20 = 15;
int avant_30 = 7;
int tourner_droite = 21;
int tourner_gauche = 21;
int tourner_180 = 7;
int arriere = 7;



Node* create_node(t_localisation pos, int valeur) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->pos = pos;
    new_node->valeur = valeur;
    new_node->num_children = 0;
    for (int i = 0; i < nb_enfant_max; i++){
        new_node->children[i] = NULL;}
    return new_node;
}

int nb_aleatoire(){
    int random_number = (rand() % 1) + 1;
    printf("Nombre aléatoire entre 1 et 7 : %d\n", random_number);

    return random_number;}


t_move mouv_aleatoire(int valeur_mouv){
    switch (valeur_mouv){
        case 1 : {
            if (avant_10 == 0) {
                return (mouv_aleatoire(nb_aleatoire()));
            } else {
                avant_10--;
                printf("F10 ");
                return F_10;
            }
        }
        case 2 : {
            if (avant_20==0){
                return (mouv_aleatoire(nb_aleatoire()));
            } else {
                avant_20-- ;
                printf("F20 ");
                return F_20 ;}
        }
        case 3 : {
            if (avant_30 == 0) {
                return (mouv_aleatoire(nb_aleatoire()));
            } else {
                avant_30--;
                printf("F30 ");
                return F_30;
            }
        }
        case 4 : {
            if (arriere == 0) {
                return (mouv_aleatoire(nb_aleatoire()));
            } else {
                arriere--;
                printf("B10 ");
                return B_10;
            }
        }
        case 5 : {
            if (tourner_gauche == 0) {
                return (mouv_aleatoire(nb_aleatoire()));
            } else {
                tourner_gauche--;
                printf("Tleft ");
                return T_LEFT;
            }
        }
        case 6 : {
            if (tourner_droite == 0) {
                return (mouv_aleatoire(nb_aleatoire()));
            } else {
                tourner_droite--;
                printf("Tright ");
                return T_RIGHT;
            }
        }
        case 7 : {
            if (tourner_180 == 0) {
                return (mouv_aleatoire(nb_aleatoire()));
            } else {
                tourner_180--;
                printf("180 ");
                return U_TURN;
            }
        }
            //default: avant_10-- ; return F_10;

    }
}
int verifier(int niveau){
    int total = avant_10+avant_20+avant_30+arriere+tourner_gauche+tourner_droite+tourner_180;
    if (total==0){
        return 5;
    }
    else if (total<niveau){
        return total ;
    }
    else{
        return 6;
    }
}

int* liste_mouve_9(){
    int* liste = (int*) malloc(9 * sizeof(int));
    if (liste == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour liste_mouve_9\n");
        return NULL;}
    for (int i =0; i<9; i++){
        liste[i]= nb_aleatoire();
    }
    return liste;
}

t_move* liste_mouve(t_localisation pos, t_map map,int* move){
    int niveau = 5;
    if (reg_case(pos,map)==1){
        niveau = 4;}
    t_move* liste = (t_move*) malloc(niveau * sizeof(t_move));

    if (liste == NULL) {
        fprintf(stderr, "Erreur d'allocation pour liste des mouvements\n");
        return NULL;
    }

    int tmp[9];
    for (int i = 0; i < 9; i++) {
        tmp[i] = move[i];
    }

    for (int i = 0; i < niveau; i++) {
        int random_index = rand() % (9 - i);
        liste[i] = mouv_aleatoire(tmp[random_index]);

        tmp[random_index] = tmp[8 - i];}

    return liste;
}


#include <stdbool.h>

void arbre_complet(Node* arbre, t_localisation position_actuel, t_map map, CheminMin* chemin_min) {
    if (reg_case(position_actuel, map) == 1) {
    }

    int* mouv9 = liste_mouve_9();
    t_move *liste_des_mouvements  = liste_mouve(position_actuel, map, mouv9);

    t_move mouv, mouv2, mouv3, mouv4, mouv5;
    t_localisation localisation_actuel, localisation_2, localisation_3, localisation_4, localisation_5;
    int cost[3];
    int nb_mouv = max_mouv;


    bool used_mouv[nb_mouv];

    for (int i = 0; i < 5; i++) {
        mouv = liste_des_mouvements[i];
        used_mouv[i] = true;

        cost_case_adj(position_actuel, map, mouv, cost);
        localisation_actuel.pos.x = cost[1];
        localisation_actuel.pos.y = cost[2];
        localisation_actuel.ori = orientation_cost_case(position_actuel, map, mouv);

        Node* child = create_node(localisation_actuel, cost[0]);
        arbre->children[arbre->num_children] = child;
        arbre->num_children++;

        if (cost[0] == 0) {
            chemin_min->valeur_min = cost[0];
            chemin_min->profondeur = 1;
            chemin_min->nodes[0] = arbre;
            chemin_min->nodes[1] = child;
            return;
        }
        if (cost[0]>100) continue;

        for (int j = 0; j < 5; j++) {
            if (used_mouv[j]) continue;

            mouv2 = liste_des_mouvements[j];


            used_mouv[j] = true;

            cost_case_adj(localisation_actuel, map, mouv2, cost);
            localisation_2.pos.x = cost[1];
            localisation_2.pos.y = cost[2];
            localisation_2.ori = orientation_cost_case(localisation_actuel, map, mouv2);

            Node* petit_enfant = create_node(localisation_2, cost[0]);
            child->children[child->num_children] = petit_enfant;
            child->num_children++;


            if (cost[0] == 0) {
                chemin_min->valeur_min = cost[0];
                chemin_min->profondeur = 2;
                chemin_min->nodes[0] = arbre;
                chemin_min->nodes[1] = child;
                chemin_min->nodes[2] = petit_enfant;
                return;
            }
            if (cost[0]>100) continue;


            for (int m = 0; m < 5; m++) {
                if (used_mouv[m]) continue;

                mouv3 = liste_des_mouvements[m];


                used_mouv[m] = true;

                cost_case_adj(localisation_2, map, mouv3, cost);
                localisation_3.pos.x = cost[1];
                localisation_3.pos.y = cost[2];
                localisation_3.ori = orientation_cost_case(localisation_2, map, mouv3);

                Node* arriere_enfant = create_node(localisation_3, cost[0]);
                petit_enfant->children[petit_enfant->num_children] = arriere_enfant;
                petit_enfant->num_children++;


                if (cost[0] == 0) {
                    chemin_min->valeur_min = cost[0];
                    chemin_min->profondeur = 3;
                    chemin_min->nodes[0] = arbre;
                    chemin_min->nodes[1] = child;
                    chemin_min->nodes[2] = petit_enfant;
                    chemin_min->nodes[3] = arriere_enfant;
                    return;
                }
                if (cost[0]>100) continue;

                for (int n = 0; n < 5; n++) {
                    if (used_mouv[n]) continue;
                    printf("valeur min %d ", chemin_min->valeur_min);
                    mouv4 = liste_des_mouvements[n];


                    used_mouv[n] = true;

                    cost_case_adj(localisation_3, map, mouv4, cost);
                    localisation_4.pos.x = cost[1];
                    localisation_4.pos.y = cost[2];
                    localisation_4.ori = orientation_cost_case(localisation_3, map, mouv4);

                    Node* arriere_arriere_enfant = create_node(localisation_4, cost[0]);
                    arriere_enfant->children[arriere_enfant->num_children] = arriere_arriere_enfant;
                    arriere_enfant->num_children++;

                    if (cost[0] == 0) {
                        chemin_min->valeur_min = cost[0];
                        chemin_min->profondeur = 4;
                        chemin_min->nodes[0] = arbre;
                        chemin_min->nodes[1] = child;
                        chemin_min->nodes[2] = petit_enfant;
                        chemin_min->nodes[3] = arriere_enfant;
                        chemin_min->nodes[4] = arriere_arriere_enfant;
                        return;
                    }
                    if (cost[0]>100) continue;


                    for (int o = 0; o < 5; o++) {
                        if (used_mouv[o]) continue;

                        mouv5 = liste_des_mouvements[o];

                        used_mouv[o] = true;

                        cost_case_adj(localisation_4, map, mouv5, cost);
                        localisation_5.pos.x = cost[1];
                        localisation_5.pos.y = cost[2];
                        localisation_5.ori = orientation_cost_case(localisation_4, map, mouv5);

                        Node* feuille = create_node(localisation_5, cost[0]);
                        arriere_arriere_enfant->children[arriere_arriere_enfant->num_children] = feuille;
                        arriere_arriere_enfant->num_children++;

                        if (cost[0] < chemin_min->valeur_min && cost[0]>0) {
                            printf("cost[0] = %d ", cost[0]);
                            chemin_min->valeur_min = cost[0];
                            printf("valeur min %d ", chemin_min->valeur_min);
                            chemin_min->profondeur = 5;
                            chemin_min->nodes[0] = arbre;
                            chemin_min->nodes[1] = child;
                            chemin_min->nodes[2] = petit_enfant;
                            chemin_min->nodes[3] = arriere_enfant;
                            chemin_min->nodes[4] = arriere_arriere_enfant;
                            printf("valeur 44min %d ", chemin_min->valeur_min);
                            chemin_min->nodes[5] = feuille;
                            printf("valeur 55min %d ", chemin_min->valeur_min);

                        }

                    }
                    for (int a =0;a<5;a++){
                        if (a==i || a== j || a == m) continue; {
                            used_mouv[a] = false;}
                    }
                }
                for (int b =0;b<5;b++){
                    if (b==i || b== j ) continue; {
                        used_mouv[b] = false;}
                }
            }
            for (int c =0;c<5;c++){
                if (c==i) continue; {
                    used_mouv[c] = false;}
            }
        }
        for (int d = 0; d < nb_mouv; d++) {
            used_mouv[d] = false;
        }

    }

}



void arbre_recurcif(Node* arbre, int niveau, t_localisation position_actuel, t_map map, CheminMin* chemin_min) {
    if (niveau == 0) {
        if (arbre->valeur < chemin_min->valeur_min) {
            chemin_min->valeur_min = arbre->valeur;
            chemin_min->profondeur = 5 - niveau;
            for (int i = 0; i < 5 - niveau; i++) {
                chemin_min->nodes[i] = arbre;
            }
        }
        return;
    }
    int* mouv9 =liste_mouve_9();
    t_move* liste_des_mouvements = liste_mouve(position_actuel,map, mouv9);
    t_move mouv;
    t_localisation localisation_actuel;
    int cost[3];
    int nb_mouv = max_mouv - niveau;

    for (int i = 0; i < nb_mouv; i++) {
        printf("1");
        mouv = liste_des_mouvements[i];
        cost_case_adj(position_actuel, map, mouv, cost);

        localisation_actuel.pos.x = cost[1];
        localisation_actuel.pos.y = cost[2];
        localisation_actuel.ori = orientation_cost_case(position_actuel, map, mouv);

        Node* enfant = create_node(localisation_actuel, cost[0]);
        arbre->children[arbre->num_children] = enfant;
        arbre->num_children++;

        if (cost[0] == 0) {
            chemin_min->valeur_min = cost[0];
            chemin_min->profondeur = 5 - niveau;
            chemin_min->nodes[5 - niveau] = enfant;
            for (int j = 0; j <= 5 - niveau; j++) {
                chemin_min->nodes[j] = arbre;
                arbre = arbre->children[arbre->num_children - 1];
            }

            free(liste_des_mouvements);
            free(mouv9);
            return;
        }

        t_move* nouveaux_mouvements = (t_move*) malloc((nb_mouv - 1) * sizeof(t_move));
        int index = 0;
        for (int j = 0; j < nb_mouv; j++) {
            if (j != i) {
                nouveaux_mouvements[index++] = liste_des_mouvements[j];
            }
        }

        return arbre_recurcif(enfant, niveau - 1, localisation_actuel, map, chemin_min);
        if (chemin_min->valeur_min == 0) {
            free(liste_des_mouvements);
            free(mouv9);
            return;}
    }

    free(liste_des_mouvements);
    free(mouv9);
}

void afficher_node(Node *node, int profondeur) {
    // Indenter selon la profondeur
    for (int i = 0; i < profondeur; i++) {
        printf("  "); // Deux espaces par niveau de profondeur
    }

    // Afficher les informations du nœud
    printf("Nœud (Profondeur %d): Position (%d, %d), Orientation %d, Valeur %d\n",
           profondeur, node->pos.pos.x, node->pos.pos.y, node->pos.ori, node->valeur);

    // Parcourir les enfants du nœud
    for (int i = 0; i < node->num_children; i++) {
        afficher_node(node->children[i], profondeur + 1); // Appel récursif pour afficher les enfants
    }
}

void afficher_arbre(Node *racine) {
    if (racine == NULL) {
        printf("L'arbre est vide.\n");
        return;
    }

    printf("Affichage de l'arbre:\n");
    afficher_node(racine, 0); // Commence à la racine avec une profondeur de 0
}