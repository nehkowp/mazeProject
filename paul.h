#ifndef PAUL_H
#define PAUL_H
#include "structure.h"

#define HAUT 122
#define BAS 115
#define GAUCHE 113
#define DROITE 100
#define HOTBAR1 49
#define HOTBAR2 50
#define HOTBAR3 51 
#define HOTBAR4 52
#define HOTBAR5 53
#define ENTER 13

extern int inversion;

#include <stdio.h>
void emptyBuffer();
char deplacementTouche(int etatJoueur);
void mazeCSV(Maze* maze);
void mazebigCSV(Maze* megamaze, int i, int j);

#endif