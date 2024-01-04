#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "stdio.h"

struct Joueur{
    int pvHealth;
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

struct Evenement{
    int positions[2];
    int type;
    char* nom;
};
struct Jeu{
    Joueur j;
    int level;
    int sizeMaze;
    int** maze;
    arbreChemins arbreChemin;
};
typedef struct Jeu Jeu;

#endif