#ifndef CLEM_H
#define CLEM_H

#include "structure.h"
#include <stdio.h>
#include "gabin.h"
void testClem();

void initJeu(Jeu* jeu);
void creerMaze(Jeu* jeu);
void placerEvents(Jeu* jeu);
void afficherScore(Jeu jeu);
void afficherInventaire(Jeu jeu);
char* emoji(int type);
arbreChemins creerArbreChemins(arbreChemins a, int positionL , int positionC, int** maze,int taille);
void neverGonnaGiveUP();
arbreChemins creerArbreCheminsCache(arbreChemins a, int positionL, int positionC,  int** maze,arbreChemins a_parent,int taille);
void afficherArbreChemins(arbreChemins a,int** maze);
int deplacementValide(int positionL, int positionC, arbreChemins* a);
void deplacementMaze(Jeu* jeu,arbreChemins* a,int*** maze, int positions[2]);
char* affichageMur(int** maze, int ligne, int colonne, int taille);
void afficherUseItem(int type);
#endif