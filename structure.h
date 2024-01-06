#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "stdio.h"

typedef enum {NONE,HEALTH,DAMAGE,FIRE,DRUNK,MILK,ARIANE,POISON,PIOCHE,FUN}itemListe;
typedef enum {ETAT_NORMAL,ETAT_DRUNK}etatListe;
typedef enum {ETAT_NON_DANGER,ETAT_FEU,ETAT_POISON}lifeListe;
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
    int etatSobreJoueur;
    int etatDangerJoueur; 
    int etatTourRestants;
};
typedef struct Joueur Joueur;

typedef struct node {
  int positions[2];
  int nbFils;
  int visited;
  int type; //0 si SPACE et 1 si END
  struct node** fils;
  struct node* parent;
}node;
typedef node* arbreChemins;

struct Jeu{
    int typeEvent; // NONE = 0 else afficher use item
    Joueur j;
    int level;
    int sizeMaze;
    int** maze;
    int** mazeSansEvent;
    arbreChemins arbreChemin;
};
typedef struct Jeu Jeu;

#endif