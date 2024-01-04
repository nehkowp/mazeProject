#ifndef CLEM_H
#define CLEM_H

#include "structure.h"
#include <stdio.h>
#include "gabin.h"
void testClem();


arbreChemins creerArbreChemins(arbreChemins a, int positionL , int positionC, int** maze);
arbreChemins creerArbreCheminsCache(arbreChemins a, int positionL, int positionC,  int** maze,arbreChemins a_parent);
void afficherArbreChemins(arbreChemins a,int** maze);
int deplacementValide(int positionL, int positionC, arbreChemins* a);
void deplacementMaze(arbreChemins* a,int*** maze, int positions[2]);
#endif