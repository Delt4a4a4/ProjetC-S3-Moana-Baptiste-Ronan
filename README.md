# ProjetC-S3
## Rover Run
![image](https://github.com/user-attachments/assets/5798baad-6813-4ac5-8f63-8a846757d289)

Note : L'illustration à été réalisée par ChatGPT.


## Description

Une brève description du projet. Par exemple :
> Ce projet est une application qui génère des cartes et permet de trouver le chemin optimal pour un robot. Il utilise des algorithmes de graphes pour simuler des déplacements sur une carte générée ou fournie.

## Fonctionnalités

- Génération de cartes aléatoires.
- Calcul de chemins optimaux en fonction des coûts.
- Visualisation des mouvements et des cartes.


### Prérequis

Assurez-vous d'avoir les outils suivants installés sur votre machine :

- Un compilateur C

### Fonction créée


#### Fichier arbre.h :

Node* create_node(t_localisation pos, int valeur);   
int nb_aleatoire();   
t_move mouv_aleatoire(int valeur_mouv);   
int verifier(int niveau);   
t_move* liste_mouve(t_localisation pos, t_map map,int* move);    
int* liste_mouve_9();   
void arbre_complet(Node* arbre, t_localisation position_actuel, t_map map,CheminMin* chemin_min);   
void arbre_recurcif(Node* arbre, int niveau, t_localisation position_actuel, t_map map, CheminMin* chemin_min);   
void afficher_node(Node *node, int profondeur);  
void afficher_arbre(Node *racine);  
void créer_carte(int largeur, int hauteur);  
void display_carte(t_map map);  
t_queue chemin_effetue(CheminMin chemin_min,t_queue file);  
t_stack chemin(CheminMin chemin,t_stack stack_x, t_stack stack_y);  
void afficher_chemin(t_stack stack_x, t_stack stack_y);  


#### Fichier chemin.h :
 
void cost_case_adj(t_localisation position, t_map map,t_move mouvement, int donnees[3]);  
t_orientation orientation_cost_case (t_localisation position, t_map map,t_move mouvement);  
int erg_case(int pos_x,int pos_y,t_map map);  
void erg_deplacement(t_move mouvement_a_ajuster, int pos_x, int pos_y,t_orientation ori_robot,t_map map, int donnees[3]);  
int reg_case(t_localisation position, t_map map);  

#### Fichier loc.h :

t_localisation loc_init(int, int, t_orientation);
int isValidLocalisation(t_position, int, int);
t_position LEFT(t_position);
t_position RIGHT(t_position);
t_position UP(t_position);
t_position DOWN(t_position);

#### Fichier map.h : 

t_map createMapFromFile(char *);
t_map createTrainingMap();
void displayMap(t_map);

#### Fichier moves.h :

char *getMoveAsString(t_move move);
t_localisation move(t_localisation, t_move);
void updateLocalisation(t_localisation *, t_move);

#### Fichier queue.h :

t_queue createQueue(int);
void enqueue(t_queue *,t_position);
t_position dequeue(t_queue *);

#### Fichier stack.h :

t_stack createStack(int);
void push(t_stack *, int);
int pop(t_stack *);
int top(t_stack);

### Equipe : 
Projet fait par : Moana Wong, Baptiste Bertrand et Ronan Mychalski.
