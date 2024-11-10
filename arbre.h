//
// Created by rwong on 01/11/2024.
//

#ifndef UNTITLED1_ARBRE_H
#define UNTITLED1_ARBRE_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "loc.h"
#include "map.h"
#include "chemin.h"
#include "moves.h"

#define nb_enfant_max 4

typedef struct Node {
    t_localisation pos;
    int valeur;
    struct Node* children[nb_enfant_max];
    int num_children;
} Node;

typedef struct {
    Node* nodes[5];
    int profondeur;
    int valeur_min;
} CheminMin;

Node* create_node(t_localisation pos, int valeur) ;
int nb_aleatoire();
t_move mouv_aleatoire(int valeur_mouv);
int verifier(int niveau);
t_move* liste_mouve(t_localisation pos, t_map map);
void arbre_complet(Node* arbre, t_localisation position_actuel, t_map map,CheminMin* chemin_min);
void arbre_recurcif(Node* arbre, int niveau, t_localisation position_actuel, t_map map, CheminMin* chemin_min);





#endif //UNTITLED1_ARBRE_H
