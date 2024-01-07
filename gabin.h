#ifndef GABIN_H
#define GABIN_H


#include "structure.h"
#define WALL 0
#define SPACE 1
#define EVENT 5
#define DIR 4
#define VALUES 19
#define PLAYER 3
#define START 3
#define END 2
#define INITIALSIZE 7

void afficherMatrice1(int** matrice , int taille);
void allouerTab1(int** tab, int taille);
void allouerTab2(int*** tab, int taille);

void afficherMatrice2(int** matrice , int taille);
int** genererMatrice(int n);
void genererChemin(int** matrice, int taille);
int mainGabin();

void setStart( int*** matrice, int taille , int randPlacement,Joueur* j);
void setEnd( int*** maze, int taille, int randPlacement);
void mazeGenerator(int*** maze,int taille);
void ajouter_pile( const int colonne, const int ligne, int** cStack, int** rStack, int *index );
void retirer_pile( const int colonne, const int ligne, int** cStack, int** rStack, int *index );
void setValues( int values[][ VALUES ], int colonne, int ligne, int taille);


#endif