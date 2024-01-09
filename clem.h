#ifndef CLEM_H
#define CLEM_H

#include "structure.h"
#include <stdio.h>
#include "gabin.h"

/**
 * \file Répertorie les fonctions et procédures de Paul Brechenmacher
*/

/** 
 * \fn initJeu(Jeu* jeu);
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void initJeu(Jeu* jeu);

/** 
 * \fn creerMaze(Jeu* jeu);
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void creerMaze(Jeu* jeu);

/** 
 * \fn placerEvents(Maze* maze,int level);
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void placerEvents(Maze* maze,int level);

/** 
 * \fn scorePrint(int scoreLen);
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void scorePrint(int scoreLen);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void afficherScore(int score, int level);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void afficherInventaire(Jeu jeu);


/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
char* emoji(int type);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void useItem(Jeu* jeu, int typeInput);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
arbreChemins creerArbreChemins(arbreChemins a, int positionL , int positionC, int** maze,int taille);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void neverGonnaGiveUP();

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
arbreChemins creerArbreCheminsCache(arbreChemins a, int positionL, int positionC,  int** maze,arbreChemins a_parent,int taille);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void afficherArbreChemins(arbreChemins a,int** maze);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void healthPotionEvent(Jeu* jeu);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
int deplacementValide(int positionL, int positionC, arbreChemins* a, Joueur j,int** maze,int taille);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void deplacementMaze(Jeu* jeu,arbreChemins* a,int*** maze, int positions[2]);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void afficherUseItem(int type);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void damageTrapEvent(Jeu* jeu);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void milkPotionEvent(Jeu* jeu);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void gameOver(int level, int score, int highscore);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void verifEvent(Jeu* jeu, int*** maze, int positionL, int positionsC);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void eventJoueur(int* typeEvent,Joueur* j,int** maze);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void ajouterItemInventaire(Jeu* jeu, int type, char* name);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
int lenInt(int score);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void getScoreCSV(Jeu* jeu);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void saveHighScoreCSV(int highScore, int newscore);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void placerKeys(Maze* maze, Joueur* j);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void jouerMaze(Jeu* jeu);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void verifPoisonFeu(Joueur* j);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void verifEtatEvent(Joueur* j,int* typeEvent);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void creerMegaMaze(Jeu* jeu);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void jouerJeu(Jeu* jeu);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void playMegaMaze(Jeu* jeu);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void playMazeSimple(Jeu* jeu);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void optionChange(Options* options, char*** optionsTab);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
int getOptions(Options* options,int numOptions);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void saveOptions(Options* options,int numOptions,int numTest);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void initOptions(char**** optionsTab,Options* options);

/** 
 * \fn choixColonneJoueeBotHard(Jeux* Jeu)
 * \author Paul Brechenmacher
 * \date  (January 7th, 2024 9:17 AM)
 * \brief  Permet de choisir la colonne pour le Bot de difficulté Hard  
*/
void freeGame(Jeu* jeu);

#endif