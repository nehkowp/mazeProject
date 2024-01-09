#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "stdio.h"

typedef enum {NONE,HEALTH,DAMAGE,FIRE,DRUNK,MILK,ARIANE,POISON,SCORE,FUN}itemListe;
typedef enum {ETAT_NORMAL,ETAT_DRUNK,ETAT_MENU,ETAT_ENTER,ETAT_OPTION}etatListe;
typedef enum {ETAT_NON_DANGER,ETAT_FEU,ETAT_POISON}lifeListe;

typedef struct coords{
    int positions[2];
    struct coords* precedent;
    struct coords* suivant;
}coords;
typedef coords* CoordsStack;

struct Item{
    int quantite;
    int type;
    char* name;
};
typedef struct Item Item;
struct Joueur{
    int pvHealth;
    Item* inventaire;
    int positions[2];
    int etatSobreJoueur; // ETAT_NORMAL,ETAT_DRUNK,ETAT_MENU,ETAT_ENTER,ETAT_OPTION
    int etatDangerJoueur; // ETAT_NON_DANGER,ETAT_FEU,ETAT_POISON
    int etatTourRestants;
    int etatCheckPoint; // 1 pas de checkpoint //0 checkpoint en cours // 2 ancien checkpoint
    int findKeys; // 0 = NON et 1 = OUI
};
typedef struct Joueur Joueur;

typedef struct node {
  int positions[2];
  int nbFils;
  int type; //2 si CHECK 1 si SPACE et 0 si END
  struct node** fils;
  struct node* parent;
}node;
typedef node* arbreChemins;

struct Maze{
    int typeMaze; // NORMAL = 1 / AVEC CLES = 0
    int typeVisited; // 1 Oui deja visité - 0 Non visité
    int sizeMaze;
    int** tabMaze;
    arbreChemins arbreChemin;

};
typedef struct Maze Maze;

struct Options{
    int typeEmoji;
    int typeMode;
    int typeLevel;
};
typedef struct Options Options;


struct Jeu{
    int typeEvent; // NONE = 0 else afficher use item
    Joueur j;
    int level;
    int score;
    int highScore;
    int posMaze[2];
    Maze maze;
    Maze** megamaze;
    Options options;
};
typedef struct Jeu Jeu;



#endif