//
// Created by rwong on 29/10/2024.
//

#ifndef UNTITLED1_CHEMIN_H
#define UNTITLED1_CHEMIN_H
#include <stdio.h>
#include "map.h"
#include "loc.h"
#include "moves.h"

void cost_case_adj(t_localisation position, t_map map,t_move mouvement, int donnees[3]);
t_orientation orientation_cost_case (t_localisation position, t_map map,t_move mouvement);
int erg_case(int pos_x,int pos_y,t_map map);
void erg_deplacement(t_move mouvement_a_ajuster, int pos_x, int pos_y,t_orientation ori_robot,t_map map, int donnees[3]);
int reg_case(t_localisation position, t_map map);
#endif //UNTITLED1_CHEMIN_H
