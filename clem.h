#ifndef CLEM_H
#define CLEM_H

#include "structure.h"
#include <stdio.h>
#include "gabin.h"
void testClem();

void initJeu(Jeu* jeu);
void creerMaze(Jeu* jeu);
void placerEvents(Jeu* jeu);
void scorePrint(int scoreLen);
void afficherScore(int score, int level);
void afficherInventaire(Jeu jeu);
char* emoji(int type);
void useItem(Jeu* jeu, int typeInput);
arbreChemins creerArbreChemins(arbreChemins a, int positionL , int positionC, int** maze,int taille);
void neverGonnaGiveUP();
arbreChemins creerArbreCheminsCache(arbreChemins a, int positionL, int positionC,  int** maze,arbreChemins a_parent,int taille);
void afficherArbreChemins(arbreChemins a,int** maze);
void healthPotionEvent(Jeu* jeu);
int deplacementValide(int positionL, int positionC, arbreChemins* a);
void deplacementMaze(Jeu* jeu,arbreChemins* a,int*** maze, int positions[2]);
void afficherUseItem(int type);
void damageTrapEvent(Jeu* jeu);
void milkPotionEvent(Jeu* jeu);
void gameOver(int level, int score);
void verifEvent(Jeu* jeu, int*** maze, int positionL, int positionsC);
void eventJoueur(int* typeEvent,Joueur* j);
void ajouterItemInventaire(Jeu* jeu, int type, char* name);
int lenInt(int score);
#endif