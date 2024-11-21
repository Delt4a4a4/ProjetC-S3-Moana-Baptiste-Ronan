#include <stdio.h>
#include <stdlib.h>
#include "chemin.h"
#include "arbre.h"

/**
 * @brief Calcule le coût pour atteindre une case adjacente en fonction de la direction et de la carte.
 * @param position La position actuelle du robot (x, y, orientation).
 * @param map La carte contenant les coûts et les types de sols.
 * @param mouvement Le mouvement effectué (F_10, F_20, T_LEFT, etc.).
 * @param donnees Tableau pour stocker les résultats : coût, coordonnées de la nouvelle position.
 */
void cost_case_adj(t_localisation position, t_map map,t_move mouvement, int donnees[3]) {
    int robot_x = position.pos.x;
    int robot_y = position.pos.y;
    t_orientation robot_ori = position.ori;
    int costAv = 0, costD = 0, costG = 0, costAr = 0, costAv20 = 0, costAv30 = 0;

    // Vérifie si la case actuelle est une case ERG
    int erg = erg_case(position.pos.x,position.pos.y, map);
    if (erg == 1 && (mouvement == F_10 || mouvement == F_20 || mouvement == F_30 || mouvement == B_10)){
        erg_deplacement(mouvement, position.pos.x , position.pos.y, robot_ori,map, donnees);
        return  ;
    }

    // Gère les mouvements selon l'orientation actuelle du robot.
    switch (robot_ori) {
        case NORTH:{
            // Calcul des coûts pour les mouvements dans la direction NORTH.
            costAv = (robot_x - 1 < 0) ? 10000 : map.costs[robot_x - 1][robot_y];
            costAv20 = (robot_x - 2 < 0) ? 10000 : map.costs[robot_x - 2][robot_y];
            costAv30 = (robot_x - 3 < 0) ? 10000 : map.costs[robot_x - 3][robot_y];
            costAr = (robot_x + 1 > map.x_max) ? 10000 : map.costs[robot_x + 1][robot_y];
            costG = (robot_y - 1 < 0) ? 10000 : map.costs[robot_x][robot_y];
            costD = (robot_y + 1 > map.y_max) ? 10000 : map.costs[robot_x][robot_y];

            // Mise à jour du tableau `donnees` en fonction du mouvement demandé.
            if (mouvement == F_10) {
                donnees[0] = costAv;
                donnees[1] = robot_x - 1;
                donnees[2] = robot_y; }
            else if (mouvement == F_20) {
                donnees[0] = costAv20;
                donnees[1] = robot_x - 2;
                donnees[2] = robot_y; }
            else if (mouvement == F_30) {
                donnees[0] = costAv30;
                donnees[1] = robot_x - 3;
                donnees[2] = robot_y; }
            else if (mouvement == B_10) {
                donnees[0] = costAr;
                donnees[1] = robot_x + 1;
                donnees[2] = robot_y; }
            else if (mouvement == T_RIGHT) {
                donnees[0] = costD;
                donnees[1] = robot_x;
                donnees[2] = robot_y; }
            else if (mouvement == T_LEFT) {
                donnees[0] = costG;
                donnees[1] = robot_x;
                donnees[2] = robot_y; }
            break;}

            // Calcul des coûts pour les mouvements dans la direction EAST.
        case EAST:{
            costAv = (robot_y + 1 > map.y_max) ? 10000 : map.costs[robot_x][robot_y + 1];
            costAv20 = (robot_y + 2 > map.y_max) ? 10000 : map.costs[robot_x][robot_y + 2];
            costAv30 = (robot_y + 3 > map.y_max) ? 10000 : map.costs[robot_x][robot_y + 3];
            costAr = (robot_y - 1 < 0) ? 10000 : map.costs[robot_x][robot_y - 1];
            costG = (robot_x - 1 < 0) ? 10000 : map.costs[robot_x][robot_y];
            costD = (robot_x + 1 > map.x_max) ? 10000 : map.costs[robot_x][robot_y];

            // Mise à jour du tableau `donnees` en fonction du mouvement demandé.
            if (mouvement == F_10){
                donnees[0] = costAv;
                donnees[1] = robot_x;
                donnees[2] = robot_y + 1; }
            else if (mouvement == F_20) {
                donnees[0] = costAv20;
                donnees[1] = robot_x;
                donnees[2] = robot_y + 2; }
            else if (mouvement == F_30) {
                donnees[0] = costAv30;
                donnees[1] = robot_x;
                donnees[2] = robot_y + 3; }
            else if (mouvement == B_10) {
                donnees[0] = costAr;
                donnees[1] = robot_x;
                donnees[2] = robot_y - 1; }
            else if (mouvement == T_RIGHT) {
                donnees[0] = costG;
                donnees[1] = robot_x;
                donnees[2] = robot_y; }
            else if (mouvement == T_LEFT) {
                donnees[0] = costD;
                donnees[1] = robot_x;
                donnees[2] = robot_y; }
            break;}

            // Calcul des coûts pour les mouvements dans la direction South.
        case SOUTH:{
            costAv = (robot_x + 1 > map.x_max) ? 10000 : map.costs[robot_x + 1][robot_y];
            costAv20 = (robot_x + 2 > map.x_max) ? 10000 : map.costs[robot_x + 2][robot_y];
            costAv30 = (robot_x + 3 > map.x_max) ? 10000 : map.costs[robot_x + 3][robot_y];
            costAr = (robot_x - 1 < 0) ? 10000 : map.costs[robot_x - 1][robot_y];
            costD = (robot_y - 1 < 0) ? 10000 : map.costs[robot_x][robot_y];
            costG = (robot_y + 1 > map.y_max) ? 10000 : map.costs[robot_x][robot_y];

            // Mise à jour du tableau `donnees` en fonction du mouvement demandé.
            if (mouvement == F_10) {
                donnees[0] = costAv;
                donnees[1] = robot_x + 1;
                donnees[2] = robot_y; }
            else if (mouvement == F_20) {
                donnees[0] = costAv20;
                donnees[1] = robot_x + 2;
                donnees[2] = robot_y; }
            else if (mouvement == F_30) {
                donnees[0] = costAv30;
                donnees[1] = robot_x + 3;
                donnees[2] = robot_y; }
            else if (mouvement == B_10) {
                donnees[0] = costAr;
                donnees[1] = robot_x - 1;
                donnees[2] = robot_y; }
            else if (mouvement == T_RIGHT) {
                donnees[0] = costD;
                donnees[1] = robot_x;
                donnees[2] = robot_y; }
            else if (mouvement == T_LEFT) {
                donnees[0] = costG;
                donnees[1] = robot_x;
                donnees[2] = robot_y; }
            break;}

            // Calcul des coûts pour les mouvements dans la direction West.
        case WEST:{
            costAv = (robot_y - 1 < 0) ? 10000 : map.costs[robot_x][robot_y - 1];
            costAv20 = (robot_y - 2 < 0) ? 10000 : map.costs[robot_x][robot_y - 2];
            costAv30 = (robot_y - 3 < 0) ? 10000 : map.costs[robot_x][robot_y - 3];
            costAr = (robot_y + 1 > map.y_max) ? 10000 : map.costs[robot_x][robot_y + 1];
            costD = (robot_x - 1 < 0) ? 10000 : map.costs[robot_x][robot_y];
            costG = (robot_x + 1 > map.x_max) ? 10000 : map.costs[robot_x][robot_y];

            // Mise à jour du tableau `donnees` en fonction du mouvement demandé.
            if (mouvement == F_10) {
                donnees[0] = costAv;
                donnees[1] = robot_x;
                donnees[2] = robot_y - 1; }
            else if (mouvement == F_20) {
                donnees[0] = costAv20;
                donnees[1] = robot_x;
                donnees[2] = robot_y - 2; }
            else if (mouvement == F_30) {
                donnees[0] = costAv30;
                donnees[1] = robot_x;
                donnees[2] = robot_y - 3; }
            else if (mouvement == B_10) {
                donnees[0] = costAr;
                donnees[1] = robot_x;
                donnees[2] = robot_y + 1; }
            else if (mouvement == T_RIGHT) {
                donnees[0] = costD;
                donnees[1] = robot_x;
                donnees[2] = robot_y; }
            else if (mouvement == T_LEFT) {
                donnees[0] = costG;
                donnees[1] = robot_x;
                donnees[2] = robot_y; }
            break;}
    }
    //if (mouvement == F_10) {
    //    printf("avancer :%d  ",costAv);}
    //else if (mouvement == F_20) {
    //        printf("avancer de 20 : %d ",costAv20);}
    //else if (mouvement == F_30) {
    //    printf("avancer de 30 : %d ",costAv30);}
    //else if (mouvement == B_10) {
    //    printf("back : %d ",costAr);}
    //else if (mouvement == T_RIGHT) {
    //    printf("droite : %d ",costD);}
    //else if (mouvement == T_LEFT) {
    //    printf("gauche : %d ",costG);}
}

/**
 * @brief Met à jour l'orientation du robot après un mouvement.
 * @param position La position actuelle du robot (contient l'orientation actuelle).
 * @param map La carte (inutile ici mais passée pour cohérence).
 * @param mouvement Le mouvement effectué (ex. T_LEFT, T_RIGHT).
 * @return La nouvelle orientation après le mouvement.
 */
t_orientation orientation_cost_case (t_localisation position, t_map map,t_move mouvement){
    t_orientation robot_ori = position.ori;
    switch (robot_ori) {
        case NORTH: {
            if (mouvement == T_LEFT) {
                robot_ori = WEST;}
            else if (mouvement == T_RIGHT) {
                robot_ori = EAST;}
            else if (mouvement == U_TURN) {
                robot_ori = SOUTH;}
            break;}

        case EAST: {
            if (mouvement == T_LEFT) {
                robot_ori = NORTH;}
            else if (mouvement == T_RIGHT) {
                robot_ori = SOUTH;}
            else if (mouvement == U_TURN) {
                robot_ori = WEST;}
            break;}

        case SOUTH: {
            if (mouvement == T_LEFT) {
                robot_ori = EAST;}
            else if (mouvement == T_RIGHT) {
                robot_ori = WEST;}
            else if (mouvement == U_TURN) {
                robot_ori = NORTH;}
            break;}

        case WEST:{
            if (mouvement == T_LEFT) {
                robot_ori = SOUTH;}
            else if (mouvement == T_RIGHT) {
                robot_ori = NORTH;}
            else if (mouvement == U_TURN) {
                robot_ori = EAST;}
            break;}

    }
    return (robot_ori);
}

/**
 * @brief Vérifie si la case actuelle une case erg.
 * @param pos_x Coordonnée x de la case.
 * @param pos_y Coordonnée y de la case.
 * @param map La carte où vérifier.
 * @return 1 si la case est spéciale (sol ergonomique), sinon 0.
 */
int erg_case(int pos_x,int pos_y,t_map map){
    if (map.soils[pos_x][pos_y]==2)
        return 1;
    else
        return 0;
}

/**
 * @brief Calcule le déplacement si le robot est sur une case erg.
 * @param mouvement_a_ajuster Le mouvement demandé.
 * @param pos_x Coordonnée x initiale.
 * @param pos_y Coordonnée y initiale.
 * @param ori_robot Orientation du robot.
 * @param map La carte contenant les coûts.
 * @param donnees Tableau pour stocker les résultats du calcul.
 */
void erg_deplacement(t_move mouvement_a_ajuster, int pos_x, int pos_y,t_orientation ori_robot,t_map map, int donnees[3]) {
    int costAv = 0, costD = 0, costG = 0, costAr = 0, costAv20 = 0, costAv30 = 0;
    switch (ori_robot) {
        case NORTH : {
            costAv = map.costs[pos_x][pos_y];
            costAv20 = (pos_x - 1 < 0) ? 10000 : map.costs[pos_x - 1][pos_y];
            costAv30 = (pos_x - 2 < 0) ? 10000 : map.costs[pos_x - 2][pos_y];
            costAr = map.costs[pos_x][pos_y];

            if (mouvement_a_ajuster == F_10) {
                donnees[0] = costAv;
                donnees[1] = pos_x;
                donnees[2] = pos_y;
            } else if (mouvement_a_ajuster == F_20) {
                donnees[0] = costAv20;
                donnees[1] = pos_x - 1;
                donnees[2] = pos_y;
            } else if (mouvement_a_ajuster == F_30) {
                donnees[0] = costAv30;
                donnees[1] = pos_x - 2;
                donnees[2] = pos_y;
            } else if (mouvement_a_ajuster == B_10) {
                donnees[0] = costAr;
                donnees[1] = pos_x;
                donnees[2] = pos_y;
            }
            break;
        }

        case EAST: {
            costAv = map.costs[pos_x][pos_y];
            costAv20 = (pos_y + 1 > map.y_max) ? 10000 : map.costs[pos_x][pos_y + 1];
            costAv30 = (pos_y + 2 > map.y_max) ? 10000 : map.costs[pos_x][pos_y + 2];
            costAr = map.costs[pos_x][pos_y];

            if (mouvement_a_ajuster == F_10) {
                donnees[0] = costAv;
                donnees[1] = pos_x;
                donnees[2] = pos_y;
            } else if (mouvement_a_ajuster == F_20) {
                donnees[0] = costAv20;
                donnees[1] = pos_x;
                donnees[2] = pos_y + 1;
            } else if (mouvement_a_ajuster == F_30) {
                donnees[0] = costAv30;
                donnees[1] = pos_x;
                donnees[2] = pos_y + 2;
            } else if (mouvement_a_ajuster == B_10) {
                donnees[0] = costAr;
                donnees[1] = pos_x;
                donnees[2] = pos_y;
            }
            break;
        }

        case SOUTH: {
            costAv = map.costs[pos_x][pos_y];
            costAv20 = (pos_x + 1 > map.x_max) ? 10000 : map.costs[pos_x + 1][pos_y];
            costAv30 = (pos_x + 2 > map.x_max) ? 10000 : map.costs[pos_x + 2][pos_y];
            costAr = map.costs[pos_x][pos_y];

            if (mouvement_a_ajuster == F_10) {
                donnees[0] = costAv;
                donnees[1] = pos_x;
                donnees[2] = pos_y;
            } else if (mouvement_a_ajuster == F_20) {
                donnees[0] = costAv20;
                donnees[1] = pos_x + 1;
                donnees[2] = pos_y;
            } else if (mouvement_a_ajuster == F_30) {
                donnees[0] = costAv30;
                donnees[1] = pos_x + 2;
                donnees[2] = pos_y;
            } else if (mouvement_a_ajuster == B_10) {
                donnees[0] = costAr;
                donnees[1] = pos_x;
                donnees[2] = pos_y;
            } else if (mouvement_a_ajuster == T_RIGHT) {
                break;
            }

            case WEST: {
                costAv = map.costs[pos_x][pos_y];
                costAv20 = (pos_y - 1 < 0) ? 10000 : map.costs[pos_x][pos_y - 1];
                costAv30 = (pos_y - 2 < 0) ? 10000 : map.costs[pos_x][pos_y - 2];
                costAr = map.costs[pos_x][pos_y];

                if (mouvement_a_ajuster == F_10) {
                    donnees[0] = costAv;
                    donnees[1] = pos_x;
                    donnees[2] = pos_y;
                } else if (mouvement_a_ajuster == F_20) {
                    donnees[0] = costAv20;
                    donnees[1] = pos_x;
                    donnees[2] = pos_y - 1;
                } else if (mouvement_a_ajuster == F_30) {
                    donnees[0] = costAv30;
                    donnees[1] = pos_x;
                    donnees[2] = pos_y - 2;
                } else if (mouvement_a_ajuster == B_10) {
                    donnees[0] = costAr;
                    donnees[1] = pos_x;
                    donnees[2] = pos_y;
                }
                break;
            }
        }
    }
}
/**
 * @brief Vérifie si la case actuelle est une zone Reg.
 * @param position Position actuelle du robot.
 * @param map Carte contenant les informations des sols.
 * @return 1 si la case est une zone réglementée, sinon 0.
 */
int reg_case(t_localisation position, t_map map){
    if (map.soils[position.pos.x][position.pos.y] == 4){
        return 1;
    }
    else
        return 0;
}
