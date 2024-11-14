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
    srand(time(NULL));
    int random_number = (rand() % 7) + 1;
    //printf("Nombre aléatoire entre 1 et 7 : %d\n", random_number);

    return random_number;}


t_move mouv_aleatoire(int valeur_mouv){
    switch (valeur_mouv){
        case 1 : {
            if (avant_10 == 0) {
                return (mouv_aleatoire(nb_aleatoire()));
            } else {
                avant_10--;
                return F_10;
            }
        }
        case 2 : {
            if (avant_20==0){
                return (mouv_aleatoire(nb_aleatoire()));
            } else {
                avant_20-- ;
                return F_20 ;}
        }
        case 3 : {
            if (avant_30 == 0) {
                return (mouv_aleatoire(nb_aleatoire()));
            } else {
                avant_30--;
                return F_30;
            }
        }
        case 4 : {
            if (arriere == 0) {
                return (mouv_aleatoire(nb_aleatoire()));
            } else {
                arriere--;
                return B_10;
            }
        }
        case 5 : {
            if (tourner_gauche == 0) {
                return (mouv_aleatoire(nb_aleatoire()));
            } else {
                tourner_gauche--;
                return T_LEFT;
            }
        }
        case 6 : {
            if (tourner_droite == 0) {
                return (mouv_aleatoire(nb_aleatoire()));
            } else {
                tourner_droite--;
                return T_RIGHT;
            }
        }
        case 7 : {
            if (tourner_180 == 0) {
                return (mouv_aleatoire(nb_aleatoire()));
            } else {
                tourner_180--;
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

t_move* liste_mouve(t_localisation pos, t_map map) {
    int niveau = 5;
    t_move* liste = (t_move*) malloc(5 * sizeof(t_move));
    int nb_mouv;
    if (liste == NULL) {
        fprintf(stderr, "probleme liste des mouvements\n");
        return NULL;
    }
    if (reg_case(pos,map)==1){
        niveau = 4;
    }

    nb_mouv = verifier(niveau);

    if (nb_mouv==6) {
        for (int i = 0; i < niveau; i++) {
            liste[i] = mouv_aleatoire(nb_aleatoire());
        }
    }
    else if (nb_mouv<5){
        for (int i = 0; i < nb_mouv; i++) {
            liste[i] = mouv_aleatoire(nb_aleatoire());}
    }
    else if (nb_mouv==5){
        printf("plus de mouvements");
    }
    return liste;
}


void arbre_complet(Node* arbre, t_localisation position_actuel, t_map map,CheminMin* chemin_min) {
    if (reg_case(position_actuel,map) == 1){

    }
    t_move *liste_des_mouvements = liste_mouve(position_actuel,map);
    t_move mouv, mouv2, mouv3, mouv4, mouv5;
    t_localisation localisation_actuel, localisation_2, localisation_3, localisation_4, localisation_5;
    int cost[3];
    int nb_mouv = max_mouv;

    for (int i = 0; i < nb_mouv; i++) {
        mouv = liste_des_mouvements[i];
        cost_case_adj(position_actuel, map, mouv, cost);

        localisation_actuel.pos.x = cost[1];
        localisation_actuel.pos.y = cost[2];
        localisation_actuel.ori = orientation_cost_case(position_actuel, map, mouv);

        Node *child = create_node(localisation_actuel, cost[0]);
        arbre->children[arbre->num_children] = child;
        arbre->num_children++;

        for (int j = 0; j < nb_mouv; j++) {
            mouv2 = liste_des_mouvements[j];
            if (mouv2 == mouv) continue;

            cost_case_adj(localisation_actuel, map, mouv2, cost);
            localisation_2.pos.x = cost[1];
            localisation_2.pos.y = cost[2];
            localisation_2.ori = orientation_cost_case(localisation_actuel, map, mouv2);

            Node *petit_enfant = create_node(localisation_2, cost[0]);
            child->children[child->num_children] = petit_enfant;
            child->num_children++;

            for (int m = 0; m < nb_mouv; m++) {
                mouv3 = liste_des_mouvements[m];
                if (mouv3 == mouv || mouv3 == mouv2) continue;

                cost_case_adj(localisation_2, map, mouv3, cost);
                localisation_3.pos.x = cost[1];
                localisation_3.pos.y = cost[2];
                localisation_3.ori = orientation_cost_case(localisation_2, map, mouv3);

                Node *arriere_enfant = create_node(localisation_3, cost[0]);
                petit_enfant->children[petit_enfant->num_children] = arriere_enfant;
                petit_enfant->num_children++;

                for (int n = 0; n < nb_mouv; n++) {
                    mouv4 = liste_des_mouvements[n];
                    if (mouv4 == mouv || mouv4 == mouv2 || mouv4 == mouv3) continue;

                    cost_case_adj(localisation_3, map, mouv4, cost);
                    localisation_4.pos.x = cost[1];
                    localisation_4.pos.y = cost[2];
                    localisation_4.ori = orientation_cost_case(localisation_3, map, mouv4);

                    Node *arriere_arriere_enfant = create_node(localisation_4, cost[0]);
                    arriere_enfant->children[arriere_enfant->num_children] = arriere_arriere_enfant;
                    arriere_enfant->num_children++;

                    for (int o = 0; o < nb_mouv; o++) {
                        mouv5 = liste_des_mouvements[o];
                        if (mouv5 == mouv || mouv5 == mouv2 || mouv5 == mouv3 || mouv5) continue;

                        cost_case_adj(localisation_3, map, mouv5, cost);
                        localisation_5.pos.x = cost[1];
                        localisation_5.pos.y = cost[2];
                        localisation_5.ori = orientation_cost_case(localisation_4, map, mouv5);

                        Node *feuille = create_node(localisation_5, cost[0]);
                        arriere_arriere_enfant->children[arriere_arriere_enfant->num_children] = feuille;
                        arriere_arriere_enfant->num_children++;

                        if (cost[0] < chemin_min->valeur_min) {
                            chemin_min->valeur_min = cost[0];
                            chemin_min->profondeur = 5;  // Profondeur du chemin
                            chemin_min->nodes[0] = arbre;
                            chemin_min->nodes[1] = child;
                            chemin_min->nodes[2] = petit_enfant;
                            chemin_min->nodes[3] = arriere_enfant;
                            chemin_min->nodes[4] = arriere_arriere_enfant;
                            chemin_min->nodes[5] = feuille;

                        }
                    }
                }
            }
        }
        free(liste_des_mouvements);
    }
}


void arbre_recurcif(Node* arbre, int niveau, t_localisation position_actuel, t_map map, CheminMin* chemin_min) {
    if (niveau == 0) {
        if (arbre->valeur < chemin_min->valeur_min) {
            chemin_min->valeur_min = arbre->valeur;
            chemin_min->profondeur = 5 - niveau;  // Profondeur actuelle
            for (int i = 0; i < 5 - niveau; i++) {
                chemin_min->nodes[i] = arbre;  // Enregistre le chemin actuel
            }
        }
        return;
    }

    t_move* liste_des_mouvements = liste_mouve(position_actuel,map);
    t_move mouv;
    t_localisation localisation_actuel;
    int cost[3];
    int nb_mouv = max_mouv - niveau;

    for (int i = 0; i < nb_mouv; i++) {
        mouv = liste_des_mouvements[i];
        cost_case_adj(position_actuel, map, mouv, cost);

        localisation_actuel.pos.x = cost[1];
        localisation_actuel.pos.y = cost[2];
        localisation_actuel.ori = orientation_cost_case(position_actuel, map, mouv);

        Node* enfant = create_node(localisation_actuel, cost[0]);
        arbre->children[arbre->num_children] = enfant;
        arbre->num_children++;

        return arbre_recurcif(enfant, niveau - 1, localisation_actuel, map, chemin_min);
    }

    free(liste_des_mouvements);
}
