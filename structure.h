#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "stdio.h"

typedef enum {NONE,HEALTH,DAMAGE,ARIANE}itemListe;

typedef struct coords{
    int positions[2];
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
};
typedef struct Joueur Joueur;

typedef struct node {
  int positions[2];
  int nbFils;
  int type; //0 si SPACE et 1 si END
  struct node** fils;
  struct node* parent;
}node;
typedef node* arbreChemins;

struct Jeu{
    Joueur j;
    int level;
    int sizeMaze;
    int** maze;
    arbreChemins arbreChemin;
};
typedef struct Jeu Jeu;

#endif